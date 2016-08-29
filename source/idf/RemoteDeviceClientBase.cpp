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
#include <unistd.h>

#include "idf/RemoteDeviceClientBase.hh"

namespace idf {

RemoteDeviceClientBase::RemoteDeviceClientBase(const std::string hostName, unsigned short hostPort) :
    host(hostName),
    port(hostPort),
    mOpen(false) {}

RemoteDeviceClientBase::~RemoteDeviceClientBase() {
    close();
}

void RemoteDeviceClientBase::setPort(unsigned short hostPort) {
    port = hostPort;
}

void RemoteDeviceClientBase::setHost(std::string hostName) {
    host = hostName;
}

bool RemoteDeviceClientBase::isOpen() {
    return mOpen;
}

void RemoteDeviceClientBase::open() {
    std::ostringstream stream;
    stream << port;

    // Get server connection information.
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *results;
    if (getaddrinfo(host.c_str(), stream.str().c_str(), &hints, &results)) {
        throw IOException("Failed to resolve host address \"" + host + "\": " + strerror(errno));
    }

    std::cout << "[RemoteDeviceClient] Connecting to " << host << ":" << port << std::endl;

    // Establish first available connection.
    struct addrinfo *currentHost;
    for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
        if ((socketHandle = socket(currentHost->ai_family,
          currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
            continue;
        }

        if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
            std::cout << "[Remote Device Client] Connected  to " << host << ":" << port << std::endl;
            break;
        }

        ::close(socketHandle);
    }

    freeaddrinfo(results);

    if (currentHost == NULL) {
        stream.clear();
        stream << " Failed to connect to " << host << ":" << port;
        throw IOException(stream.str());
    }

    mOpen = true;
}

void RemoteDeviceClientBase::close() {
    mOpen = false;
    ::close(socketHandle);
}

void RemoteDeviceClientBase::transmit() {
    if (!mOpen) {
        throw IOException("Connection is not open.");
    }
}

}
