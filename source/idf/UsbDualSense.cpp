#include "idf/UsbDualSense.hh"
#include "idf/IOException.hh"

#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <cstring>
#include <iostream>

namespace idf {

UsbDualSense::UsbDualSense() :
    UsbDualShock("Playstation 5 DualSense", 64) {
    command[2] = 0x05; // report ID
    command[3] = 0xFF; // enable motors
}

void UsbDualSense::decode(const std::vector<unsigned char>& data) {
    leftAnalogLeftRightPivot.setValue(data[1]);
    leftAnalogUpDownPivot.setValue(data[2]);
    rightAnalogLeftRightPivot.setValue(data[3]);
    rightAnalogUpDownPivot.setValue(data[4]);

    leftTrigger.setValue(data[5]);
    rightTrigger.setValue(data[6]);

    shareButton.setValue(data[6] >> 4 & 1);
    optionsButton.setValue(data[6] >> 5 & 1);
    leftAnalogIn.setValue(data[6] >> 6 & 1);
    rightAnalogIn.setValue(data[6] >> 7 & 1);

    psButton.setValue(data[7] & 1);
    trackpad.button.setValue(data[7] >> 1 & 1);
    mute.setValue(data[7] >> 2 & 1);

    unsigned char dPad = data[8] & 0xF;
    directionalPadRight.setValue(dPad == 1 || dPad == 2 || dPad == 3);
    directionalPadDown.setValue(dPad == 3 || dPad == 4 || dPad == 5);
    directionalPadLeft.setValue(dPad == 5 || dPad == 6 || dPad == 7);
    directionalPadUp.setValue(dPad == 7 || dPad == 0 || dPad == 1);

    squareButton.setValue(data[8] >> 4 & 1);
    xButton.setValue(data[8] >> 5 & 1);
    circleButton.setValue(data[8] >> 6 & 1);
    triangleButton.setValue(data[8] >> 7 & 1);

    leftBumper.setValue(data[9] & 1);
    rightBumper.setValue(data[9] >> 1 & 1);
    leftTriggerDiscrete.setValue(data[9] >> 2 & 1);
    leftTriggerDiscrete.setValue(data[9] >> 3 & 1);

    anglularVelocityX.setValue(short(data[17] << 8 | data[16]));
    anglularVelocityY.setValue(short(data[19] << 8 | data[18]));
    anglularVelocityZ.setValue(short(data[21] << 8 | data[20]));

    accelerationX.setValue(short(data[23] << 8 | data[22]));
    accelerationY.setValue(short(data[25] << 8 | data[24]));
    accelerationZ.setValue(short(data[27] << 8 | data[26]));

    trackpad.finger1.contact.setValue(data[33] >> 7);
    trackpad.finger1.x.setValue((data[35] & 0x0F) << 8 | data[34] );
    trackpad.finger1.y.setValue(data[36] << 4 | data[35] >> 4);

    trackpad.finger2.contact.setValue(data[37] >> 7);
    trackpad.finger2.x.setValue((data[39] & 0xF) << 8 | data[38]);
    trackpad.finger2.y.setValue(data[40] << 4 | data[39] >> 4);
}

void UsbDualSense::sendCommand() {
    if (!mOpen) {
        UsbDevice::open();
    }
    hid_write(hidDevice, &command[2], 32);
}

}
