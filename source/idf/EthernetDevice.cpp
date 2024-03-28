#include "idf/EthernetDevice.hh"
#include "idf/IOException.hh"

#include <errno.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace idf {

EthernetDevice::EthernetDevice(const std::string& id, unsigned length) :
   InputDevice(id),
   packetLength(length) {}

void EthernetDevice::open() {
    if (!mOpen) {

        std::ostringstream stream;
        stream << "[IDF::EthernetDevice::open()] ";

        socketHandle = socket(AF_INET, SOCK_STREAM, 0);

        if ( errno > 0) {
            stream << "failed to create socket";
            perror(stream.str().c_str());
            throw IOException(stream.str());
        }

        struct sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(serverPort);
        serverAddress.sin_addr.s_addr = inet_addr(serverName.c_str());

        std::cout << "[IDF::EthernetDevice] Connecting to " << serverName << ":" << serverPort << std::endl;

        if (connect(socketHandle, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
            stream << "failed to connect to device " << serverName << ":" << serverPort;
            perror(stream.str().c_str());
            throw IOException(stream.str());
        }

        std::cout << "[IDF::EthernetDevice] Connected  to " << serverName << ":" << serverPort << std::endl;

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
    bytesRecvd = recv(socketHandle, buffer, length, MSG_DONTWAIT);
    if (bytesRecvd < 0) {
        if (errno == EAGAIN) { // no data, try again later
            return 0;
        } else {
            close();
            throw IOException("Error " + std::to_string(bytesRecvd) + " while reading " + name + ": " + strerror(errno));
        }
    }
    return bytesRecvd;
}

int EthernetDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        open();
    }
    int bytesSent = send(socketHandle, buffer, length, MSG_NOSIGNAL);
    if (bytesSent < 0) {
        close();
        throw IOException("Error while writing " + name + ": " + strerror(errno));
    }

    return bytesSent;
}

} // namespace
