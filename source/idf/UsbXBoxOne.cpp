#include "idf/UsbXBoxOne.hh"

namespace idf {

UsbXBoxOne::UsbXBoxOne() :
    UsbDevice("Xbox One Controller", 17) {}

void UsbXBoxOne::decode(const std::vector<unsigned char>& data) {
    if (data[0] == 1) {
        directionalPadUp.setValue((data[13] & 7) == 1);
        directionalPadDown.setValue((data[13] & 7) == 5);
        directionalPadLeft.setValue((data[13] & 7) == 7);
        directionalPadRight.setValue((data[13] & 7) == 3);

        viewButton.setValue(data[16] >> 0 & 1);
        xBoxButton.setValue(data[15] >> 4 & 1);
        menuButton.setValue(data[15] >> 3 & 1);

        leftBumper.setValue(data[14] >> 6 & 1);
        rightBumper.setValue(data[14] >> 7 & 1);

        aButton.setValue(data[14] >> 0 & 1);
        bButton.setValue(data[14] >> 1 & 1);
        xButton.setValue(data[14] >> 3 & 1);
        yButton.setValue(data[14] >> 4 & 1);

        leftAnalogLeftRightPivot.setValue((int)(u_char)data[2] << 8 | data[1]);
        leftAnalogUpDownPivot.setValue((int)(u_char)data[4] << 8 | data[3]);
        leftAnalogTrigger.setValue((int)(u_char)data[10] << 8 | data[9]);

        rightAnalogLeftRightPivot.setValue((int)(u_char)data[6] << 8 | data[5]);
        rightAnalogUpDownPivot.setValue((int)(u_char)data[8] << 8 | data[7]);
        rightAnalogTrigger.setValue((int)(u_char)data[12] << 8 | data[11]);
    }
}

}
