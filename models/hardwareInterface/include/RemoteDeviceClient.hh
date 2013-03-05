/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/RemoteDeviceClient.cpp))
 */

#ifndef _REMOTE_DEVICE_CLIENT_HH_
#define _REMOTE_DEVICE_CLIENT_HH_

#include "RemoteDeviceServerBase.hh"
#include "inputAbstraction/include/Utils.hh"
#include "IOException.hh"

#include <iostream>
#include <sstream>
#include <exception>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

namespace idf {

/**
 * transmits commands from a contained <code>T</code> to a corresponding
 * <code>RemoteDeviceServer<T></code>
 *
 * @author Derek Bankieris
 */
template <class T, class U>
class RemoteDeviceClient {

    public:

    /** the controller whose commands are to be transmitted */
    const T& controller;

    /**
     * constructs an instance that transmits commands from
     * <code>sourceController</code> to the <code>RemoteDeviceServer<T></code>
     * listening on <code>host</code>:<code>port</code>
     *
     * @param sourceController the command source
     * @param host the name or ip address of the server host machine
     * @param port the port on which the server is listening
     */
    RemoteDeviceClient(const T& sourceController, const std::string host, unsigned short port) :
        controller(sourceController) {

        std::stringstream ss;
        ss << port;

        // Get server connection information.
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        struct addrinfo *results;
        if (getaddrinfo(host.c_str(), ss.str().c_str(), &hints, &results)) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to resolve host address: " << strerror(errno);
            throw IOException(oss.str());
        }

        // Establish first available connection.
        struct addrinfo *currentHost;
        for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
            if ((socketHandle = socket(currentHost->ai_family,
              currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
                continue;
            }

            if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
                std::cout << __FILE__ << ":" << __LINE__
                          << " Connected to " << host << ":" << port << std::endl;
                break;
            }

            close(socketHandle);
        }

        freeaddrinfo(results);

        if (currentHost == NULL) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to connect to " << host << ":" << port << ": " << strerror(errno);
            throw IOException(oss.str());
        }
    }


    /** destructor */
    virtual ~RemoteDeviceClient() {
        close(socketHandle);
    }

    /** sends the commands to the server */
    void transmit() {
        U commands;
        packCommands(commands, controller);

        if (write(socketHandle, &commands, sizeof(commands)) == -1) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to write: " << strerror(errno);
            throw IOException(oss.str());
        }
    }


    protected:

    /** the socket */
    int socketHandle;

    /**
     * packs commands from <code>controller</code> into <code>commands</code>
     *
     * @param commands the structure into which the commands are packed
     * @param controller the controller whose commands are to be packed
     */
    virtual void packCommands(U& commands, const T& controller) = 0;

    /**
     * packs the normalized <code>value</code> into a short
     *
     * @param value the normalized value
     */
    static unsigned char pack(double value) {
        return (signed char)(bound(value) * RemoteDeviceServerBase::serializationFactor);
    }

};

}

#endif
