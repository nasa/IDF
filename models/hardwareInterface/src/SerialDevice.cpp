#include "hardwareInterface/include/SerialDevice.hh"
#include "hardwareInterface/include/IOException.hh"

#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

namespace idf {

SerialDevice::SerialDevice(const std::string& id, const char *terminalPath) :
    InputDevice(id),
    path(terminalPath) {}

void SerialDevice::open() {
    if (!mOpen) {
        /**
         * Some kernels respect the DCD (data carrier detect) control signal and
         * block on open until the device indicates that it's ready. However,
         * some serial devices don't use control signals anymore, resulting in an
         * indefinite hang. Thus, open in non-blocking mode and then immediately
         * return to blocking.
         */
        handle = ::open(path.c_str(), O_NOCTTY | O_RDWR | O_NONBLOCK);

        if (handle == -1) {
            throw IOException("Failed to open " + path + ": " + std::strerror(errno));
        }

        int options = fcntl(handle, F_GETFL);
        if (options == -1) {
            throw IOException("Failed to get options for " + path + ": " + std::strerror(errno));
        }

        options &= ~O_NONBLOCK;
        options = fcntl(handle, F_SETFL, options);
        if (options == -1) {
            throw IOException("Failed to set options for " + path + ": " + std::strerror(errno));
        }

        mOpen = true;
    }
}

int SerialDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesRead = ::read(handle, buffer, length);

    if (bytesRead < 0) {
        close();
        throw IOException("Error while reading " + name + ": " + strerror(errno));
    }

    return bytesRead;
}

int SerialDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesWritten = ::write(handle, buffer, length);

    if (bytesWritten < 0) {
        close();
        throw IOException("Error while writing " + name + ": " + strerror(errno));
    }

    return bytesWritten;
}

void SerialDevice::close() {
    if (mOpen) {
        ::close(handle);
        mOpen = false;
    }
}

}
