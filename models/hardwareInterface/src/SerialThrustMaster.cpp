#include "SerialThrustMaster.hh"

#include <iostream>

using namespace idf;

SerialThrustMaster::SerialThrustMaster(const char *terminalPath) :
    SerialDevice(terminalPath) {}

void SerialThrustMaster::update() {
    SerialDevice::update();

    char request = 'r';

    write(&request, sizeof(request));

    int bytesRemaining = 9;
    unsigned char buffer[bytesRemaining];

    while(bytesRemaining) {
        bytesRemaining -= read(buffer + (9 - bytesRemaining), bytesRemaining);
    }

    forwardBackwardPivot.setValue(buffer[0]);
    twist.setValue(buffer[1]);
    leftRightPivot.setValue(buffer[2]);
    leftRightTranslation.setValue(buffer[3]);
    upDownTranslation.setValue(buffer[4]);
    forwardBackwardTranslation.setValue(buffer[5]);
    trigger.setValue(buffer[8] & 1);
    leftButton.setValue(buffer[8] >> 1 & 1);
    middleButton.setValue(buffer[8] >> 2 & 1);
    rightButton.setValue(buffer[8] >> 3 & 1);
}
