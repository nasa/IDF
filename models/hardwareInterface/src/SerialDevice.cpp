#include "SerialDevice.hh"
#include "IOException.hh"

#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <unistd.h>

using namespace idf;

SerialDevice::SerialDevice(const char *terminalPath) :
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

        if (handle < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to open " << path << ".";
            throw IOException(oss.str());
        }

        int options = fcntl(handle, F_GETFL);
        if (options < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to get options for " << path << ".";
            throw IOException(oss.str());
        }

        options &= ~O_NONBLOCK;
        options = fcntl(handle, F_SETFL, options);
        if (options < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to set options for " << path << ".";
            throw IOException(oss.str());
        }

        mOpen = true;
    }
}

int SerialDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: device is not open.";
        throw IOException(oss.str());
    }

    int bytesRead = ::read(handle, buffer, length);

    if (bytesRead < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: " << strerror(errno);
        throw IOException(oss.str());
    }

    return bytesRead;
}

int SerialDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while writing: device is not open.";
        throw IOException(oss.str());
    }

    int bytesWritten = ::write(handle, buffer, length);

    if (bytesWritten < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while writing: " << strerror(errno);
        throw IOException(oss.str());
    }

    return bytesWritten;
}

void SerialDevice::close() {
    if (mOpen) {
        ::close(handle);
        mOpen = false;
    }
}
