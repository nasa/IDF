#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/IOException.hh"
#include <sstream>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <exception>

#include <arpa/inet.h>

using namespace idf;

const double RemoteDeviceServerBase::serializationFactor = 100;

RemoteDeviceServerBase::RemoteDeviceServerBase(unsigned short listenPort) :
    InputDevice("Remote Device Server"),
    port(listenPort) {}

RemoteDeviceServerBase::~RemoteDeviceServerBase() {
    close();
};

void RemoteDeviceServerBase::open() {
    if ((socket = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to create socket: " << strerror(errno);
        throw IOException(oss.str());
    }

    if (fcntl(socket, F_SETFL, O_NONBLOCK) == -1) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to set socket to non-blocking: " << strerror(errno);
        throw IOException(oss.str());
    }

    struct sockaddr_in socketAddress;
    memset(&socketAddress, 0, sizeof(socketAddress));
    socketAddress.sin_family = AF_UNSPEC;
    socketAddress.sin_port = htons(port);
    socketAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket, (struct sockaddr*)&socketAddress, sizeof(socketAddress)) == -1) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__;
        if (port) {
            oss << " Failed to bind to port " << port << ":" << strerror(errno);
        }
        else {
            oss << " Failed to bind to any port:" << strerror(errno);
        }
        throw IOException(oss.str());
    }

    if (listen(socket, SOMAXCONN) == -1) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Socket failed to listen: " << strerror(errno);
        throw IOException(oss.str());
    }

    mOpen = true;
}

void RemoteDeviceServerBase::close() {
    if (!isOpen()) {
        ::close(socket);
        mOpen = false;
    }
}

void RemoteDeviceServerBase::setPort(unsigned short listenPort) {
    port = listenPort;
}

unsigned short RemoteDeviceServerBase::getPort() const {
    if (isOpen()) {
        struct sockaddr_storage listenAddress;
        socklen_t length = sizeof(listenAddress);

        if (getsockname(socket, (struct sockaddr*)&listenAddress, &length)) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to retrieve socket information: "
                << strerror(errno);
            throw std::runtime_error(oss.str());
        }

        switch (listenAddress.ss_family) {
            case AF_INET:
                return ntohs(((struct sockaddr_in*)&listenAddress)->sin_port);
            case AF_INET6:
                return ntohs(((struct sockaddr_in6*)&listenAddress)->sin6_port);
            default:
                std::ostringstream oss;
                oss << __FILE__ << ":" << __LINE__
                    << " Unknown socket family." << strerror(errno);
                throw std::runtime_error(oss.str());
        }
    }

    return port;
}

double RemoteDeviceServerBase::unpack(signed char value) {
    return value / serializationFactor;
}
