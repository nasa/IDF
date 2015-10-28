/**
 * PURPOSE:
 * ()
 */

#ifndef _REMOTE_DEVICE_SERVER_HH_
#define _REMOTE_DEVICE_SERVER_HH_

#include "hardwareInterface/include/RemoteDeviceServerBase.hh"
#include "hardwareInterface/include/IOException.hh"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

namespace idf {

/**
 * a server which accepts and manages connections from multiple
 * {@link RemoteDeviceClient}s
 *
 * @author Derek Bankieris
 */
template <class T>
class RemoteDeviceServer : public RemoteDeviceServerBase {

    public:

    /**
     * constructs an instance which listens for connections on
     * <code>port</code>
     *
     * @param port the port over which to vectoren for connections
     */
    RemoteDeviceServer(unsigned short listenPort = 0) :
        RemoteDeviceServerBase(listenPort) {}

    /**
     * destructor
     */
    virtual ~RemoteDeviceServer() {};

    /**
     * calls <code>acceptPendingConnections()</code> followed by
     * <code>readFromClients()</code>
     */
    virtual void update() {
        acceptPendingConnections();
        readFromClients();
    }

    /**
     * accepts all pending client connections
     */
    void acceptPendingConnections() {
        int clientSocket;
        struct sockaddr_storage client;
        socklen_t length = sizeof(client);

        while ((clientSocket = accept(socket, (struct sockaddr*)&client, &length)) != -1) {
            std::cout << __FILE__ << ":" << __LINE__
                      << " Accepted connection request from ";

            char name[1024] = "unknown";
            if (client.ss_family == AF_INET) {
                struct sockaddr_in *ipv4Client = (struct sockaddr_in *)&client;
                inet_ntop(AF_INET, &ipv4Client->sin_addr, name, sizeof(name));
                std::cout << name << ":" << ntohs(ipv4Client->sin_port);
            }
            else if (client.ss_family == AF_INET6) {
                struct sockaddr_in6 *ipv6Client = (struct sockaddr_in6 *)&client;
                inet_ntop(AF_INET6, &ipv6Client->sin6_addr, name, sizeof(name));
                std::cout << name << ":" << ntohs(ipv6Client->sin6_port);
            }
            std::cout << std::endl;

            if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
                ::close(clientSocket);
                std::cout << __FILE__ << ":" << __LINE__
                    << " Failed to set client socket to non-blocking: "
                    << strerror(errno) << std::endl;
            }
            else {
                clients.push_back(Client(clientSocket, client));
            }
        }
    }

    /**
     * receives data from all clients
     */
    void readFromClients() {
        typename std::vector<class Client>::iterator i = clients.begin();

        while (i != clients.end()) {
            int bytesRead;
            do {
                bytesRead = read(i->socket, &i->commands, sizeof(i->commands));
            } while (bytesRead > 0);

            if (bytesRead == 0 || errno != EAGAIN) {
                std::cout << __FILE__ << ":" << __LINE__ << " ";

                if (bytesRead == 0) {
                    std::cout << "Lost connection to remote controller at ";
                }
                else {
                    std::cout << "Failed to read (" << strerror(errno)
                              << ") from remote controller at ";
                }

                char name[1024] = "unknown";
                if (i->address.ss_family == AF_INET) {
                    struct sockaddr_in *ipv4Client = (struct sockaddr_in *)&i->address;
                    inet_ntop(AF_INET, &ipv4Client->sin_addr, name, sizeof(name));
                    std::cout << name << ":" << ntohs(ipv4Client->sin_port);
                }
                else if (i->address.ss_family == AF_INET6) {
                    struct sockaddr_in6 *ipv6Client = (struct sockaddr_in6 *)&i->address;
                    inet_ntop(AF_INET6, &ipv6Client->sin6_addr, name, sizeof(name));
                    std::cout << name << ":" << ntohs(ipv6Client->sin6_port);
                }
                std::cout << std::endl;

                i = clients.erase(i);
            }
            else {
                ++i;
            }
        }
    }

    protected:

    class Client {

        public:

        /** the socket's file descriptor */
        int socket;

        /** the remote address */
        struct sockaddr_storage address;

        /** the serialized commands */
        T commands;

        /**
         * constructs an instance representing a connection to a client on
         * the socket specified by <code>fileDescriptor</code>
         *
         * @param the socket's handle
         */
        Client(int fileDescriptor, struct sockaddr_storage& remoteAddress) :
            socket(fileDescriptor),
            address(remoteAddress),
            commands() {}

    };

    /** the connected clients */
    std::vector<Client> clients;

};

}

#endif
