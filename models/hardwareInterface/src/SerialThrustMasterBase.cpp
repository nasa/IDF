#include "hardwareInterface/include/SerialThrustMasterBase.hh"
#include "hardwareInterface/include/IOException.hh"
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <cstring>
#include <sstream>

namespace idf {

SerialThrustMasterBase::SerialThrustMasterBase(const std::string& id, const char *terminalPath, bool isMale) :
    ThrustMasterBase(isMale),
    SerialDevice(id, terminalPath) {}

void SerialThrustMasterBase::open() {
    SerialDevice::open();

    struct termios settings;
    if (tcgetattr(handle, &settings) == -1) {
        throw IOException(name + " failed to get termios attributes: " + std::strerror(errno));
    }

    if (cfsetspeed(&settings, B9600) == -1) {
        throw IOException(name + " failed to set baud speed: " + std::strerror(errno));
    }

    // set the terminal to "raw" mode, see TERMIOS(3)
    settings.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | ICRNL | IXON | IXOFF);
    settings.c_oflag &= ~OPOST;
    settings.c_cflag &= ~(CSIZE | PARENB | CSTOPB | HUPCL);
    settings.c_cflag |= CS8 | CLOCAL | CREAD;
    settings.c_lflag &= ~(ISIG | ICANON | ECHO | ECHOE | ECHOK | ECHONL | IEXTEN);
    settings.c_cc[VTIME] = 0;
    settings.c_cc[VMIN] = 0;

    if (tcsetattr(handle, TCSANOW, &settings) == -1) {
        throw IOException(name + " failed to set termios attributes: " + std::strerror(errno));
    }

    // start getting data
    requestData();
}

std::vector<std::vector<unsigned char> > SerialThrustMasterBase::read() {
    std::vector<std::vector<unsigned char> > results;

    int availableBytes;
    if (ioctl(handle, FIONREAD, &availableBytes) == -1) {
        throw IOException("Failed to get number of bytes available for " + name + ": " + std::strerror(errno));
    }

    // If a full packet is available or a timeout has occurred, process all available data.
    if (availableBytes >= 9 || getTime() > timeout) {
        int remainingBytes = availableBytes;
        std::vector<unsigned char> buffer(remainingBytes);

        /**
         * While we know how many bytes are avialable, read can still be interrupted by signals,
         * so call it in a loop.
         */
        while (remainingBytes) {
            remainingBytes -= SerialDevice::read(&buffer[0] + (availableBytes - remainingBytes), remainingBytes);
        }

        /**
         * Only return the data to the caller if exactly one full packet arrived. If a timeout
         * occurred or extra bytes arrived, discard all of the data.
         */
        if (availableBytes == 9) {
            results.push_back(buffer);
        }

        /**
         * Request the next state update from the device. Sending requests too quickly can corrupt
         * the device's output, so we only send a new request when at least a full packet has
         * arrived or a timeout occured.
         */
        requestData();
    }

    return results;
}

void SerialThrustMasterBase::decode(const std::vector<unsigned char>& data) {
    forwardBackwardPivot.setValue(data[0]);
    twist.setValue(data[1]);
    leftRightPivot.setValue(data[2]);
    leftRightTranslation.setValue(data[3]);
    upDownTranslation.setValue(data[4]);
    forwardBackwardTranslation.setValue(data[5]);
    trigger.setValue(data[8] & 1 ? 1 : data[8] & 2 ? -1 : 0);

    processButtons(data[8]);
}

void SerialThrustMasterBase::requestData() {
    static const char request = 'r';
    write(&request, sizeof(request));
    timeout = getTime() + 0.1;
}

}
