#include "hardwareInterface/include/SerialThrustMasterBase.hh"
#include "hardwareInterface/include/IOException.hh"
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <sys/ioctl.h>

namespace idf {

SerialThrustMasterBase::SerialThrustMasterBase(const std::string& id, const char *terminalPath, bool isMale) :
    ThrustMasterBase(isMale),
    SerialDevice(id, terminalPath) {}

void SerialThrustMasterBase::open() {
    SerialDevice::open();

    struct termios settings;
    tcgetattr(handle, &settings);
    cfsetspeed(&settings, B9600);
    settings.c_cflag |= (CLOCAL | CREAD);
    settings.c_cflag &= ~PARENB;
    settings.c_cflag &= ~CSTOPB;
    settings.c_cflag &= ~CSIZE;
    settings.c_cflag |= CS8;
}

std::vector<std::vector<unsigned char> > SerialThrustMasterBase::read() {
    const char request = 'r';
    write(&request, sizeof(request));

    std::vector<std::vector<unsigned char> > results;
    while (true) {

        int availableBytes;
        if (ioctl(handle, FIONREAD, &availableBytes) == -1) {
            throw IOException("Failed to get number of bytes available for " + name + ".");
        }
        if (availableBytes < 9) {
            break;
        }

        int bytesRemaining = 9;
        std::vector<unsigned char> buffer(bytesRemaining);
        while (bytesRemaining) {
            bytesRemaining -= SerialDevice::read(&buffer[0] + (9 - bytesRemaining), bytesRemaining);
        }

        results.push_back(buffer);
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

}
