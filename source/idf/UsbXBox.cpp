#include "idf/UsbXBox.hh"

namespace idf {

UsbXBox::UsbXBox(int vendorID, int productID) :
    UsbDevice("X Box Controller", vendorID, productID, 14) {}

void UsbXBox::decode(const std::vector<unsigned char>& data) {
    directionalPadUp.setValue(data[2] & 1);
    directionalPadDown.setValue(data[2] >> 1 & 1);
    directionalPadLeft.setValue(data[2] >> 2 & 1);
    directionalPadRight.setValue(data[2] >> 3 & 1);

    startButton.setValue(data[2] >> 4 & 1);
    backButton.setValue(data[2] >> 5 & 1);
    leftAnalogIn.setValue(data[2] >> 6 & 1);
    rightAnalogIn.setValue(data[2] >> 7 & 1);

    leftBumper.setValue(data[3] & 1);
    rightBumper.setValue(data[3] >> 1 & 1);
    xBoxButton.setValue(data[3] >> 2 & 1);

    aButton.setValue(data[3] >> 4 & 1);
    bButton.setValue(data[3] >> 5 & 1);
    xButton.setValue(data[3] >> 6 & 1);
    yButton.setValue(data[3] >> 7 & 1);

    leftTrigger.setValue(data[4]);
    rightTrigger.setValue(data[5]);

    leftAnalogLeftRightPivot.setValue((int)(char)data[7] << 8 | data[6]);
    leftAnalogUpDownPivot.setValue((int)(char)data[9] << 8 | data[8]);

    rightAnalogLeftRightPivot.setValue((int)(char)data[11] << 8 | data[10]);
    rightAnalogUpDownPivot.setValue((int)(char)data[13] << 8 | data[12]);
}

}
