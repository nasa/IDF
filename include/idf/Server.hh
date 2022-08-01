/*
PURPOSE:
*/

/** @trick_parse{everything} */

#ifndef SERVER_HH
#define SERVER_HH

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "idf/Manageable.hh"
#include "idf/IOException.hh"

namespace idf {

/**
 * a server which accepts and manages connections from multiple {@link Client}s
 *
 * @author Derek Bankieris
 */
template <class T>
class Server : public Manageable {

    public:

    /**
     * constructs an instance which listens for connections on @a port
     *
     * @param port @copydoc listenPort
     */
    Server(unsigned short port = 0) :
        listenPort(port) {}

    /** destructor */
    virtual ~Server() {
        for (typename std::vector<class Client*>::iterator i = clients.begin(); i != clients.end(); ++i) {
            delete *i;
        }
        close();
    };

    /**
     * begins listening for client connections on the port returned by getPort()
     *
     * @throws IOException if an error occurs
     */
    void open(){
        if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            throw IOException("Failed to create socket: " + std::string(strerror(errno)));
        }

        if (fcntl(socket, F_SETFL, O_NONBLOCK) == -1) {
            throw IOException("Failed to set socket to non-blocking: " + std::string(strerror(errno)));
        }

        struct sockaddr_in socketAddress;
        memset(&socketAddress, 0, sizeof(socketAddress));
        socketAddress.sin_family = AF_UNSPEC;
        socketAddress.sin_port = htons(listenPort);
        socketAddress.sin_addr.s_addr = INADDR_ANY;

        if (bind(socket, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) == -1) {
            std::ostringstream stream;
            if (listenPort) {
                stream << "Failed to bind to port " << listenPort << ":" << strerror(errno);
            }
            else {
                stream << "Failed to bind to any port:" << strerror(errno);
            }
            throw IOException(stream.str());
        }

        if (listen(socket, SOMAXCONN) == -1) {
            throw IOException("Socket failed to listen: " + std::string(strerror(errno)));
        }

        Manageable::open();
    }

    virtual void update() {
        acceptPendingConnections();

        typename std::vector<class Client*>::iterator i = clients.begin();
        while (i != clients.end()) {
            Client& client = **i;
            try {
                client.update();
                ++i;
            }
            catch (const IOException& ioException) {
                std::cout << "[Server] " << ioException.what() << std::endl;
                delete &client;
                i = clients.erase(i);
            }
        }
    }

    /** terminates existing client connections and stops listening for new ones */
    void close() {
        if (!isOpen()) {
            ::close(socket);
            Manageable::close();
        }
    }

    /** accepts all pending client connections */
    void acceptPendingConnections() {
        int clientSocket;
        struct sockaddr_storage client;
        socklen_t length = sizeof(client);

        while ((clientSocket = accept(socket, (struct sockaddr*)&client, &length)) != -1) {
            Client* newClient = new Client(clientSocket, client);
            std::cout << "[Server] Accepted connection request from "
                << newClient->getName() << std::endl;

            if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
                ::close(clientSocket);
                std::cout << "[Server] Failed to set client socket to non-blocking: "
                    << strerror(errno) << std::endl;
            }
            else {
                clients.push_back(newClient);
            }
        }
    }

    /**
     * Sets the port on which this instance should listen for connections the
     * next time open() is called. A value of @c 0 indicates that the first
     * available port should be used.
     *
     * @param port @copydoc listenPort
     */
    void setPort(unsigned short port) {
        listenPort = port;
    }

    /**
     * Returns the actual port on which this instance is listening for client
     * connections if isOpen() returns @c true. Returns the designated port
     * otherwise.
     *
     * @return @copydoc listenPort
     *
     * @throws IOException if an error occurs
     */
    unsigned short getPort() const {
        if (isOpen()) {
            struct sockaddr_storage listenAddress;
            socklen_t length = sizeof(listenAddress);

            if (getsockname(socket, (struct sockaddr*)&listenAddress, &length)) {
                throw std::runtime_error("Failed to retrieve socket information: " + std::string(strerror(errno)));
            }

            switch (listenAddress.ss_family) {
                case AF_INET:
                    return ntohs(((struct sockaddr_in*)&listenAddress)->sin_port);
                case AF_INET6:
                    return ntohs(((struct sockaddr_in6*)&listenAddress)->sin6_port);
                default:
                    throw std::runtime_error("Unknown socket family.");
            }
        }

        return listenPort;
    }

    /**
     * unpacks the @a value packed by Client::pack
     *
     * @param value the packed value
     *
     * @return the normalized value
     */
    static double unpack(signed char value) {
        return value / 100.0;
    }

    protected:

    /** server-managed client information */
    class Client {

        public:

        /** the socket's file descriptor */
        const int socket;

        /**
         * constructs an instance representing a connection to a client at @a address
         * on the socket specified by @a fileDescriptor
         *
         * @param fileDescriptor the socket's handle
         * @param address the address of the client
         */
        Client(int fileDescriptor, struct sockaddr_storage& address) :
            socket(fileDescriptor) {
            char buffer[1024] = "unknown";
            if (address.ss_family == AF_INET) {
                struct sockaddr_in *ipv4Client = (struct sockaddr_in *)&address;
                inet_ntop(AF_INET, &ipv4Client->sin_addr, buffer, sizeof(buffer));
            }
            else if (address.ss_family == AF_INET6) {
                struct sockaddr_in6 *ipv6Client = (struct sockaddr_in6 *)&address;
                inet_ntop(AF_INET6, &ipv6Client->sin6_addr, buffer, sizeof(buffer));
            }
            name = std::string(buffer);
        }

        ~Client() {
            ::close(socket);
        }

        const std::string& getName() const {
            return name;
        }

        const T& getCommands() const {
            return commands;
        }

        void update() {
            int bytesRead;
            while ((bytesRead = ::read(socket, &commands, sizeof(commands))) > 0) {}

            if (bytesRead == 0) {
                throw IOException("Lost connection to " + name);
            }
            else if (errno != EAGAIN) {
                throw IOException(std::string("Failed to read (") + strerror(errno) + ") from " + name);
            }
        }

        private:

        /** the host machine's name */
        std::string name;

        /** the packed commands */
        T commands;

    };

    /**
     * accumate a field across all clients
     *
     * @param field the field that will be accumulated
     * @param function a functor or function pointer that takes two
     *   arguments and returns one value, all of accessor's type, used to
     *   sequentially accumulate the fields
     *
     * @return the accumulated value
     */
    template<class U, class BinaryOperation>
    double accumulateClientValues(const U T::*field, const BinaryOperation& function) const {
        double result = U();
        for (typename std::vector<Client*>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
            result = function(result, unpack((*i)->getCommands().*field));
        }
        return result;
    }

    private:

    /** the listening socket */
    int socket;

    /** the port over which to listen for clients */
    unsigned short listenPort;

    /** the connected clients */
    std::vector<Client*> clients;

};

}

#endif
