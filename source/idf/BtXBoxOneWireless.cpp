#include "idf/BtXBoxOneWireless.hh"
#include <iomanip>
#include <iostream>
#include "hidapi/hidapi/hidapi.h"
namespace idf {

BtXBoxOneWireless::BtXBoxOneWireless() :
    UsbDevice("Xbox One Wireless Controller", 16) {}

void BtXBoxOneWireless::decode(const std::vector<unsigned char>& data) {
    if (data[0] == 1) {
        directionalPadUp.setValue(false);
        directionalPadDown.setValue(false);
        directionalPadLeft.setValue(false);
        directionalPadRight.setValue(false);
        switch (data[13] & 0x0F) { // handle diagonals
            case(1):
                directionalPadUp.setValue(true);
                break;
            case(2):
                directionalPadUp.setValue(true);
                directionalPadRight.setValue(true);
                break;
            case(3):
                directionalPadRight.setValue(true);
                break;
            case(4):
                directionalPadRight.setValue(true);
                directionalPadDown.setValue(true);
                break;
            case(5):
                directionalPadDown.setValue(true);
                break;
            case(6):
                directionalPadLeft.setValue(true);
                directionalPadDown.setValue(true);
                break;
            case(7):
                directionalPadLeft.setValue(true);
                break;
            case (8):
                directionalPadUp.setValue(true);
                directionalPadLeft.setValue(true);
                break;
        }

        aButton.setValue(data[14] >> 0 & 0x1);
        bButton.setValue(data[14] >> 1 & 0x1);
        xButton.setValue(data[14] >> 2 & 0x1);
        yButton.setValue(data[14] >> 3 & 0x1);

        leftBumper.setValue(data[14] >> 4 & 0x1);
        rightBumper.setValue(data[14] >> 5 & 0x1);

        viewButton.setValue(data[14] >> 6 & 0x1);
        menuButton.setValue(data[14] >> 7 & 0x1);

        leftAnalogIn.setValue(data[15] >> 0 & 0x1);
        rightAnalogIn.setValue(data[15] >> 1 & 0x1);

        leftAnalogLeftRightPivot.setValue((int)(unsigned char)data[2] << 8 | data[1]);
        leftAnalogUpDownPivot.setValue((int)(unsigned char)data[4] << 8 | data[3]);
        leftAnalogTrigger.setValue((int)(unsigned char)(data[10] & 0x3) << 8 | data[9]);

        rightAnalogLeftRightPivot.setValue((int)(unsigned char)data[6] << 8 | data[5]);
        rightAnalogUpDownPivot.setValue((int)(unsigned char)data[8] << 8 | data[7]);
        rightAnalogTrigger.setValue((int)(unsigned char)(data[12] & 0x3) << 8 | data[11]);
    }
    else if (data[0] == 2) {
        xBoxButton.setValue(data[1] & 0x1);
    }
}

}
