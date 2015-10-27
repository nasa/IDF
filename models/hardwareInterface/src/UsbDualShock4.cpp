#include "UsbDualShock4.hh"
#include "IOException.hh"

#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <cstring>
#include <iostream>

using namespace idf;

UsbDualShock4::UsbDualShock4(int vendorID, int productID) :
    UsbDualShock(vendorID, productID) {
    command[2] = 0x05; // report ID
    command[3] = 0xFF; // enable motors
}

void UsbDualShock4::update() {
    UsbDevice::update();

    unsigned char buffer[64];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        leftAnalogLeftRightPivot.setValue(buffer[1]);
        leftAnalogUpDownPivot.setValue(buffer[2]);
        rightAnalogLeftRightPivot.setValue(buffer[3]);
        rightAnalogUpDownPivot.setValue(buffer[4]);

        squareButton.setValue(buffer[5] >> 4 & 1);
        xButton.setValue(buffer[5] >> 5 & 1);
        circleButton.setValue(buffer[5] >> 6 & 1);
        triangleButton.setValue(buffer[5] >> 7 & 1);

        unsigned char dPad = buffer[5] & 0xF;
        directionalPadRight.setValue(dPad == 1 || dPad == 2 || dPad == 3);
        directionalPadDown.setValue(dPad == 3 || dPad == 4 || dPad == 5);
        directionalPadLeft.setValue(dPad == 5 || dPad == 6 || dPad == 7);
        directionalPadUp.setValue(dPad == 7 || dPad == 0 || dPad == 1);

        leftBumper.setValue(buffer[6] & 1);
        rightBumper.setValue(buffer[6] >> 1 & 1);
        shareButton.setValue(buffer[6] >> 4 & 1);
        optionsButton.setValue(buffer[6] >> 5 & 1);
        leftAnalogIn.setValue(buffer[6] >> 6 & 1);
        rightAnalogIn.setValue(buffer[6] >> 7 & 1);

        psButton.setValue(buffer[7] & 1);
        trackpad.button.setValue(buffer[7] >> 1 & 1);

        leftTrigger.setValue(buffer[8]);
        rightTrigger.setValue(buffer[9]);

        trackpad.finger1.contact.setValue(buffer[35] >> 7);
        trackpad.finger1.x.setValue((buffer[37] & 0xF) << 8 | buffer[36]);
        trackpad.finger1.y.setValue(buffer[38] << 4 | buffer[37] >> 4);

        trackpad.finger2.contact.setValue(buffer[39] >> 7);
        trackpad.finger2.x.setValue((buffer[41] & 0xF) << 8 | buffer[40]);
        trackpad.finger2.y.setValue(buffer[42] << 4 | buffer[41] >> 4);
    }
}

void UsbDualShock4::sendCommand() {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Device is not open.";
        throw IOException(oss.str());
    }
    hid_write(hidDevice, &command[2], 32);
}
