#include "idf/UsbXBoxOne.hh"
#include <iomanip>
#include <iostream>
#include "hidapi/hidapi/hidapi.h"
namespace idf {

UsbXBoxOne::UsbXBoxOne() :
    UsbDevice("Xbox One S Controller [Bluetooth]", 17) {}

void UsbXBoxOne::decode(const std::vector<unsigned char>& data) {
    if (data[0] == 1) {
        leftAnalogLeftRightPivot.setValue((int)(unsigned char)data[2] << 8 | data[1]);
        leftAnalogUpDownPivot.setValue((int)(unsigned char)data[4] << 8 | data[3]);
        leftAnalogTrigger.setValue((int)(unsigned char)(data[10] & 0x3) << 8 | data[9]);

        rightAnalogLeftRightPivot.setValue((int)(unsigned char)data[6] << 8 | data[5]);
        rightAnalogUpDownPivot.setValue((int)(unsigned char)data[8] << 8 | data[7]);
        rightAnalogTrigger.setValue((int)(unsigned char)(data[12] & 0x3) << 8 | data[11]);

        directionalPadUp.setValue((data[13] & 7) == 1);
        directionalPadDown.setValue((data[13] & 7) == 5);
        directionalPadLeft.setValue((data[13] & 7) == 7);
        directionalPadRight.setValue((data[13] & 7) == 3);

        aButton.setValue(data[14] >> 0 & 0x1);
        bButton.setValue(data[14] >> 1 & 0x1);
        xButton.setValue(data[14] >> 3 & 0x1);
        yButton.setValue(data[14] >> 4 & 0x1);

        leftBumper.setValue(data[14] >> 6 & 0x1);
        rightBumper.setValue(data[14] >> 7 & 0x1);

        xBoxButton.setValue(data[15] >> 4 & 0x1);
        menuButton.setValue(data[15] >> 3 & 0x1);
        viewButton.setValue(data[16] >> 0 & 0x1);
    }
}

}
