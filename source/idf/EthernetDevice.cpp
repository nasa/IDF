#include "idf/EthernetDevice.hh"
#include "idf/IOException.hh"

#include <errno.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace idf {

EthernetDevice::EthernetDevice(const std::string& name, const std::string& address, const int port) :
   InputDevice(name),
   ipAddress(address),
   port(port) {}

void EthernetDevice::open() {
    throw(std::logic_error("Not Implemented. Stub."));
}

void EthernetDevice::close() {
    throw(std::logic_error("Not Implemented. Stub."));
}

int EthernetDevice::read(unsigned char *buffer, size_t length) {
    throw(std::logic_error("Not Implemented. Stub."));
    return 0;
}

int EthernetDevice::write(unsigned char *buffer, size_t length) {
    throw(std::logic_error("Not Implemented. Stub."));
    return 0;
}

} // namespace
