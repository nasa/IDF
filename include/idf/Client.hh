/*
PURPOSE:
*/

/** @trick_parse{everything} */

#ifndef CLIENT_HH
#define CLIENT_HH

#include "idf/Manageable.hh"
#include "idf/Server.hh"
#include "idf/Utils.hh"
#include "idf/IOException.hh"

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
 * transmits commands from a contained @a T to a corresponding {@link Server}\<T\>
 *
 * @param T the source of commands to transmit
 * @param U structure into which commands are packed
 *
 * @author Derek Bankieris
 */
template <class T, class U>
class Client : public Manageable {

    public:

    /** destructor */
    virtual ~Client() {
        close();
    }

    /**
     * attempts to establish a connection to the server
     *
     * @throws IOException if an error occurs
     */
    void open() {
        // Get server connection information.
        struct addrinfo hints;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;

        std::ostringstream stream;
        stream << serverPort;
        struct addrinfo *results;
        if (getaddrinfo(serverName.c_str(), stream.str().c_str(), &hints, &results)) {
            throw IOException("Failed to resolve server address \"" + serverName + "\": " + strerror(errno));
        }

        std::cout << "[Client] Connecting to " << serverName << ":" << serverPort << std::endl;

        // Establish first available connection.
        struct addrinfo *currentHost;
        for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
            if ((socketHandle = socket(currentHost->ai_family,
              currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
                continue;
            }

            if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
                std::cout << "[Client] Connected  to " << serverName << ":" << serverPort << std::endl;
                break;
            }

            ::close(socketHandle);
        }

        freeaddrinfo(results);

        if (currentHost == NULL) {
            stream.str("");
            stream << "Failed to connect to " << serverName << ":" << serverPort;
            throw IOException(stream.str());
        }

        Manageable::open();
    }

    /** disconnects from the server */
    void close() {
        ::close(socketHandle);
        Manageable::close();
    }

    /**
     * sets the host to which this instance will attempt to connect the next
     * time open() is called
     *
     * @param host @copydoc serverName
     */
    void setHost(const std::string& host) {
        serverName = host;
    }

    /**
     * sets the server port to which this instance will attempt to connect the
     * next time open() is called
     *
     * @param port @copydoc serverPort
     */
    void setPort(unsigned short port) {
        serverPort = port;
    }

    protected:

    /** source whose commands are to be transmitted */
    const T& source;

    /**
     * constructs an instance that transmits commands from @a commandSource
     * to the Server \<T\> listening on <em>host</em>:<em>port</em>
     *
     * @param commandSource @copydoc source
     * @param host @copydoc serverName
     * @param port @copydoc serverPort
     */
    Client(const T& commandSource, const std::string& host, unsigned short port) :
        source(commandSource),
        serverName(host),
        serverPort(port) {}

    /**
     * sends the commands to the server
     *
     * @throws IOException if an error occurs
     */
    void update() {
        Manageable::update();

        U commands;
        packCommands(commands);

        if (write(socketHandle, &commands, sizeof(commands)) == -1) {
            close();
            throw IOException("Failed to write: " + std::string(strerror(errno)));
        }
    }

    /**
     * packs commands from @a source into @a commands
     *
     * @param commands the structure into which the commands are packed
     */
    virtual void packCommands(U& commands) = 0;

    /**
     * packs the normalized @a value into a @c char
     *
     * @param value the normalized value
     *
     * @return the packed value
     */
    static unsigned char pack(double value) {
        return (signed char)(bound(value) * 100.0);
    }

    private:

    /** the name or ip address of the server */
    std::string serverName;

    /** the port on which the server is listening */
    unsigned short serverPort;

    /** the socket */
    int socketHandle;

};

}

#endif
