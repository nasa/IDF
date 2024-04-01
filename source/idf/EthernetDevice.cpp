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

EthernetDevice::EthernetDevice(const std::string& id, unsigned length) :
    InputDevice(id),
    packetLength(length),
    sockType(SOCK_STREAM),
    tcp(true) {
        memset(&serverAddr, 0 , sizeof(serverAddr));
        
    }

void EthernetDevice::open() {
    if (!mOpen) {

        std::ostringstream stream;
        stream << "[IDF::EthernetDevice::open()] ";

        socketHandle = socket(AF_INET, sockType, 0);

        if ( errno > 0) {
            stream << "failed to create socket";
            perror(stream.str().c_str());
            throw IOException(stream.str());
        }

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        serverAddr.sin_addr.s_addr = inet_addr(serverName.c_str());
        serverAddrLen = sizeof(serverAddr);

        std::cout << "[IDF::EthernetDevice] Connecting to " << serverName << ":" << serverPort << std::endl;

        if(tcp) {
            if (connect(socketHandle, (struct sockaddr*)&serverAddr, serverAddrLen) < 0) {
                stream << "failed to connect to TCP device " << serverName << ":" << serverPort;
                perror(stream.str().c_str());
                throw IOException(stream.str());
            }
        } else {
            char sendBuffer[] = "hello HC";
            if(sendto(socketHandle, sendBuffer, sizeof(sendBuffer), 0, (struct sockaddr *)&serverAddr, serverAddrLen) < 0) {
                stream << "failed to connect to UDP device " << serverName << ":" << serverPort;
                perror(stream.str().c_str());
                throw IOException(stream.str());
            }

        }

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
unsigned EthernetDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesRecvd = 0;

    // non-blocking receive
    bytesRecvd = recvfrom(socketHandle, buffer, length, MSG_DONTWAIT, (struct sockaddr*)&srcAddr, &srcAddrLen);
    if (bytesRecvd < 0) {
        if (errno == EAGAIN) { // no data, try again later
            return 0;
        } else {
            close();
            std::ostringstream stream;
            stream << "Error while reading from " << name;
            perror(stream.str().c_str());
        }
    }
    return bytesRecvd;
}

int EthernetDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        open();
    }
    int bytesSent = sendto(socketHandle, buffer, length, MSG_NOSIGNAL, (struct sockaddr *)&serverAddr, serverAddrLen);
    if (bytesSent < 0) {
        close();
        throw IOException("Error while writing " + name + ": " + strerror(errno));
    }

    return bytesSent;
}

} // namespace
