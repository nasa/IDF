#include "idf/UsbDualShock4.hh"
#include "idf/IOException.hh"

#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <cstring>
#include <iostream>

namespace idf {

UsbDualShock4::UsbDualShock4(int vendorID, int productID) :
    UsbDualShock("Playstation 4 Controller", vendorID, productID, 64) {
    command[2] = 0x05; // report ID
    command[3] = 0xFF; // enable motors
}

void UsbDualShock4::decode(const std::vector<unsigned char>& data) {
    leftAnalogLeftRightPivot.setValue(data[1]);
    leftAnalogUpDownPivot.setValue(data[2]);
    rightAnalogLeftRightPivot.setValue(data[3]);
    rightAnalogUpDownPivot.setValue(data[4]);

    squareButton.setValue(data[5] >> 4 & 1);
    xButton.setValue(data[5] >> 5 & 1);
    circleButton.setValue(data[5] >> 6 & 1);
    triangleButton.setValue(data[5] >> 7 & 1);

    unsigned char dPad = data[5] & 0xF;
    directionalPadRight.setValue(dPad == 1 || dPad == 2 || dPad == 3);
    directionalPadDown.setValue(dPad == 3 || dPad == 4 || dPad == 5);
    directionalPadLeft.setValue(dPad == 5 || dPad == 6 || dPad == 7);
    directionalPadUp.setValue(dPad == 7 || dPad == 0 || dPad == 1);

    leftBumper.setValue(data[6] & 1);
    rightBumper.setValue(data[6] >> 1 & 1);
    shareButton.setValue(data[6] >> 4 & 1);
    optionsButton.setValue(data[6] >> 5 & 1);
    leftAnalogIn.setValue(data[6] >> 6 & 1);
    rightAnalogIn.setValue(data[6] >> 7 & 1);

    psButton.setValue(data[7] & 1);
    trackpad.button.setValue(data[7] >> 1 & 1);

    leftTrigger.setValue(data[8]);
    rightTrigger.setValue(data[9]);

    trackpad.finger1.contact.setValue(data[35] >> 7);
    trackpad.finger1.x.setValue((data[37] & 0xF) << 8 | data[36]);
    trackpad.finger1.y.setValue(data[38] << 4 | data[37] >> 4);

    trackpad.finger2.contact.setValue(data[39] >> 7);
    trackpad.finger2.x.setValue((data[41] & 0xF) << 8 | data[40]);
    trackpad.finger2.y.setValue(data[42] << 4 | data[41] >> 4);
}

void UsbDualShock4::sendCommand() {
    if (!mOpen) {
        UsbDevice::open();
    }
    hid_write(hidDevice, &command[2], 32);
}

}
