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

    /**
     * The device can take over 10 ms to return data, which is too long to block for, so see if all
     * of the data has arrived before we start reading.
     * */
    int availableBytes;
    if (ioctl(handle, FIONREAD, &availableBytes) == -1) {
        throw IOException("Failed to get number of bytes available for " + name + ": " + std::strerror(errno));
    }

    if (availableBytes >= 9) {
        int remainingBytes = availableBytes;
        std::vector<unsigned char> buffer(remainingBytes);

        /**
         * While we know a full packet has been received, read can still be interrupted by signals,
         * so call it in a loop.
         */
        while (remainingBytes) {
            remainingBytes -= SerialDevice::read(&buffer[0] + (availableBytes - remainingBytes), remainingBytes);
        }
        results.push_back(buffer);

        /**
         * Sending requests too quickly can corrupt the device's output, so we only allow at most
         * one pending request. Since we just received a full packet, send a new request now.
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
}

}
