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

#include "RemoteDeviceClientBase.hh"

using namespace idf;

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
            << " Failed to resolve host address \"" << host << "\": " << strerror(errno);
        throw IOException(oss.str());
    }

    std::cout << __FILE__ << ":" << __LINE__
              << " Connecting to " << host << ":" << port << std::endl;

    // Establish first available connection.
    struct addrinfo *currentHost;
    for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
        if ((socketHandle = socket(currentHost->ai_family,
          currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
            continue;
        }

        if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
            std::cout << __FILE__ << ":" << __LINE__
                      << " Connected  to " << host << ":" << port << std::endl;
            break;
        }

        ::close(socketHandle);
    }

    freeaddrinfo(results);

    if (currentHost == NULL) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to connect to " << host << ":" << port;
        throw IOException(oss.str());
    }

    mOpen = true;
}

void RemoteDeviceClientBase::close() {
    mOpen = false;
    ::close(socketHandle);
}

void RemoteDeviceClientBase::transmit() {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Connection is not open.";
        throw IOException(oss.str());
    }
}
