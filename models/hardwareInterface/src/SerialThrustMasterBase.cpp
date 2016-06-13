#include "hardwareInterface/include/SerialThrustMasterBase.hh"
#include "hardwareInterface/include/IOException.hh"
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <sstream>

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

    // Set a timeout of 0.1 seconds
    settings.c_lflag &= ~ICANON;
    settings.c_cc[VTIME] = 1;
    settings.c_cc[VMIN] = 0;

    if (tcsetattr(handle, TCSANOW, &settings) == -1) {
        throw IOException("Failed to set serial port attributes: " + std::string(strerror(errno)));
    }
}

std::vector<std::vector<unsigned char> > SerialThrustMasterBase::read() {
    const char request = 'r';
    write(&request, sizeof(request));

    int bytesRemaining = 9;
    std::vector<unsigned char> buffer(bytesRemaining);

    while (bytesRemaining) {
        int bytesRead = SerialDevice::read(&buffer[0] + (9 - bytesRemaining), bytesRemaining);
        if (bytesRead == 0) {
            throw IOException("Timeout while reading " + name + ".");
        }
        bytesRemaining -= bytesRead;
    }

    std::vector<std::vector<unsigned char> > results;
    results.push_back(buffer);
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
