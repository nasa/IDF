#include "SerialDevice.hh"
#include "IOException.hh"

#include <errno.h>
#include <fcntl.h>
#include <cstring>
#include <sstream>
#include <stdio.h>

using namespace idf;

SerialDevice::SerialDevice(const char *terminalPath) :
  path(terminalPath) {}

void SerialDevice::open() {
    if (!mOpen) {
        handle = ::open(path.c_str(), O_NOCTTY | O_RDWR);

        if (handle < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to open " << path << ".";
            throw IOException(oss.str().c_str());
        }

        mOpen = true;
    }
}

int SerialDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: device is not open.";
        throw IOException(oss.str().c_str());
    }

    int bytesRead = ::read(handle, buffer, length);

    if (bytesRead < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: " << strerror(errno);
        throw IOException(oss.str().c_str());
    }

    return bytesRead;
}

int SerialDevice::write(const void *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while writing: device is not open.";
        throw IOException(oss.str().c_str());
    }

    int bytesWritten = ::write(handle, buffer, length);

    if (bytesWritten < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while writing: " << strerror(errno);
        throw IOException(oss.str().c_str());
    }

    return bytesWritten;
}

void SerialDevice::close() {
    if (mOpen) {
        ::close(handle);
        mOpen = false;
    }
}
