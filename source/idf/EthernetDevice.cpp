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
        setTCP(); // ensure vars are zeroed out.
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

        char sendBuffer[] = "hello HC";
        int ret = -1;
        while (1) {
            ret = tcp ? connect(socketHandle, (struct sockaddr*)&serverAddr, serverAddrLen)
                      : sendto(socketHandle, sendBuffer, sizeof(sendBuffer), 0, (struct sockaddr *)&serverAddr, serverAddrLen);
            if(ret < 0) {
                if (errno == EINTR) { continue; } // interrupted by a SIGNAL; retry
                stream << "failed to connect to " << (tcp ? "TCP" : "UDP") << " device " << serverName << ":" << serverPort;
                perror(stream.str().c_str());
                throw IOException(stream.str());
            }
            break;
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
    unsigned bytesTotal = 0;
    unsigned char readBuff[length];
    memset(&readBuff, 0, length);

    while(bytesTotal < length) {
        // non-blocking receive
        bytesRecvd = recvfrom(socketHandle, &readBuff[bytesTotal], length-bytesTotal, MSG_DONTWAIT, (struct sockaddr*)&srcAddr, &srcAddrLen);
        if (bytesRecvd < 0) {
            if (errno == EAGAIN) { return 0; } // no data, try again later
            else if (errno == EINTR) { continue; } // interrupted, retry
            else {
                close();
                std::string errmsg("Error while reading from ");
                errmsg.append(name);
                perror(errmsg.c_str());
                break;
            }
        } else if (bytesRecvd > 0) {
            bytesTotal += static_cast<unsigned>(bytesRecvd);
        }
    }
    memcpy(buffer, &readBuff, length);
    return bytesTotal;
}

unsigned EthernetDevice::peek(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesRecvd = 0;
    unsigned bytesTotal = 0;
    unsigned char readBuff[length];
    memset(&readBuff, 0, length);

    while(bytesTotal < length) {
        // non-blocking receive
        bytesRecvd = recvfrom(socketHandle, &readBuff[bytesTotal], length-bytesTotal, MSG_DONTWAIT | MSG_PEEK, (struct sockaddr*)&srcAddr, &srcAddrLen);
        if (bytesRecvd < 0) {
            if (errno == EAGAIN) { return 0; } // no data, try again later
            else if (errno == EINTR) { continue; } // interrupted, retry
            else {
                close();
                std::string errmsg("Error while reading from ");
                errmsg.append(name);
                perror(errmsg.c_str());
                break;
            }
        } else if (bytesRecvd > 0) {
            bytesTotal += static_cast<unsigned>(bytesRecvd);
        }
    }
    memcpy(buffer, &readBuff, length);
    return bytesTotal;
}

int EthernetDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesSent = 0;
    unsigned bytesTotal = 0;

    while (bytesTotal < length) {
        bytesSent = sendto(socketHandle, (&buffer)[bytesTotal], length-bytesTotal, MSG_NOSIGNAL, (struct sockaddr *)&serverAddr, serverAddrLen);
        if (bytesSent < 0) {
            if (errno == EINTR) { continue; } // interrupted by SIGNAL; retry
            close();
            perror("Error sending to client");
            break;
        } else if (bytesSent > 0) {
            bytesTotal += static_cast<unsigned>(bytesSent);
        }
    }
    return bytesSent;
}

} // namespace
