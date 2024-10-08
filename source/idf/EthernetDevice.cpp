#include "idf/EthernetDevice.hh"
#include "idf/IOException.hh"

#include <errno.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

namespace idf {

EthernetDevice::EthernetDevice(const std::string& id, const std::string& host, unsigned short port, unsigned length) :
    InputDevice(id),
    packetLength(length),
    serverName(host),
    serverPort(port) {
        memset(&serverAddr, 0 , sizeof(serverAddr));
        setTCP();
    }

void EthernetDevice::open() {
    if (!mOpen) {

        std::ostringstream stream;
        stream << "[IDF::EthernetDevice::open()] ";

        socketHandle = socket(AF_INET, sockType, 0);

        if (socketHandle < 0) {
            stream << "failed to create socket";
            perror(stream.str().c_str());
            throw IOException(stream.str());
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = inet_addr(serverName.c_str());
        serverAddrLen = sizeof(serverAddr);

        std::cout << "[IDF::EthernetDevice] Connecting to " << serverName << ":" << serverPort << std::endl;

        int ret = -1;
        while (1) {
            if (tcp) {
                ret = connect(socketHandle, (struct sockaddr*)&serverAddr, serverAddrLen);
            } else {
                std::vector<unsigned char> udpGreeting = getUdpGreeting();
                ret = sendto(socketHandle, &udpGreeting[0], udpGreeting.size(), 0, (struct sockaddr *)&serverAddr, serverAddrLen);
            }
            if(ret < 0) {
                if (errno == EINTR) { continue; } // interrupted by a SIGNAL; retry
                stream << "failed to connect to " << (tcp ? "TCP" : "UDP") << " device " << serverName << ":" << serverPort;
                perror(stream.str().c_str());
                throw IOException(stream.str());
            }
            break;
        }
        lastPacketArrived = std::time(nullptr);
        std::cout << "[IDF::EthernetDevice] Connected to " << serverName << ":" << serverPort << std::endl;

        Manageable::open();
    }
}

/** disconnects from the server */
void EthernetDevice::close() {
    if (mOpen) {
        ::close(socketHandle);
        Manageable::close();
    }
}

std::vector<std::vector<unsigned char> > EthernetDevice::read() {
    std::vector<std::vector<unsigned char> > results;
    std::vector<unsigned char> buffer(packetLength);

    while (read(&buffer[0], buffer.size())) {
        results.push_back(buffer);
    }

    return results;
}

size_t EthernetDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    ssize_t bytesRecvd = 0;
    size_t bytesTotal = 0;

    while(bytesTotal < length) {
        // non-blocking receive
        srcAddrLen = sizeof(srcAddr);
        bytesRecvd = tcp ? recv(socketHandle, &buffer[bytesTotal], length-bytesTotal, MSG_DONTWAIT)
                         : recvfrom(socketHandle, &buffer[bytesTotal], length-bytesTotal, MSG_DONTWAIT, (struct sockaddr*)&srcAddr, &srcAddrLen);
        if (bytesRecvd < 0) {
            if (errno == EAGAIN) { // no data, try again later
                if(std::time(nullptr) >= (lastPacketArrived + 2)) {
                    close();
                }
                return 0;
            } else if (errno == EINTR) { continue; } // interrupted, retry
            else {
                close();
                throw IOException("Error while reading " + name + ": " + strerror(errno));
            }
        } else if (bytesRecvd > 0) {
            bytesTotal += static_cast<size_t>(bytesRecvd);
            lastPacketArrived = std::time(nullptr);
        }
    }
    return bytesTotal;
}

size_t EthernetDevice::peek(unsigned char *buffer, size_t max) {
    if (!mOpen) {
        open();
    }

    ssize_t bytesRecvd = 0;

    while(1) {
        // 1 attempt at a non-blocking receive. Loop just to allow for Interrupt signals
        srcAddrLen = sizeof(srcAddr);
        bytesRecvd = tcp ? recv(socketHandle, &buffer[0], max, MSG_DONTWAIT | MSG_PEEK)
                         : recvfrom(socketHandle, &buffer[0], max, MSG_DONTWAIT | MSG_PEEK, (struct sockaddr*)&srcAddr, &srcAddrLen);
        if (bytesRecvd < 0) {
            if (errno == EAGAIN) { // no data, try again later
                if(std::time(nullptr) >= (lastPacketArrived + 2)) {
                    printf("\tPacket timeout: closing\n");
                    close();
                }
                return 0;
            } else if (errno == EINTR) { continue; } // interrupted, retry
            else {
                close();
                throw IOException("Error while reading " + name + ": " + strerror(errno));
            }
        } else if (bytesRecvd > 0) {
            return static_cast<size_t>(bytesRecvd);
            lastPacketArrived = std::time(nullptr);
        }
    }
    return 0;
}

size_t EthernetDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    ssize_t bytesSent = 0;
    size_t bytesTotal = 0;

    while (bytesTotal < length) {
        bytesSent = sendto(socketHandle, (&buffer)[bytesTotal], length-bytesTotal, MSG_NOSIGNAL, (struct sockaddr *)&serverAddr, serverAddrLen);
        if (bytesSent < 0) {
            if (errno == EINTR) { continue; } // interrupted by SIGNAL; retry
            else {
                close();
                throw IOException("Error while writing to " + name + ": " + strerror(errno));
            }
        } else if (bytesSent > 0) {
            bytesTotal += static_cast<size_t>(bytesSent);
        }
    }
    return bytesSent;
}

} // namespace
