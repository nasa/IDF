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

EthernetDevice::EthernetDevice(const std::string& name) :
   InputDevice(name) {}

void EthernetDevice::open() {
    // get server connection information
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

    struct addrinfo *currentHost;
    bool connected = false;
    for (int ii = 0; ii < retryLimit; ++ii) {
        for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
            if ((socketHandle = socket(currentHost->ai_family,
                 currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
                    continue;
            }

            if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
                std::cout << "[Client] Connected  to " << serverName << ":" << serverPort << std::endl;
                connected = true;
                break;
            }

            ::close(socketHandle);
        }
        
        if (connected) {
              break;
        } else {
            std::cout << "[Client] Connection failed - attempting reconnect to " << serverName << ":" << serverPort << std::endl;
            sleep(1);
        }

        freeaddrinfo(results);

        if(not connected) {
            stream.str("");
            stream << "Failed to connect to " << serverName << ":" << serverPort;
            throw IOException(stream.str());
        }
        Manageable::open();
    }

    throw(std::logic_error("Not Implemented. Stub."));
}

/** disconnects from the server */
void EthernetDevice::close() {
    if (mOpen) {
        ::close(socketHandle);
        Manageable::close();
    }
}

int EthernetDevice::read(unsigned char *buffer, size_t length) {
    throw(std::logic_error("Not Implemented. Stub."));
    return 0;
}

int EthernetDevice::write(const void *buffer, size_t length) {
    throw(std::logic_error("Not Implemented. Stub."));
    return 0;
}

} // namespace
