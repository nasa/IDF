#include "UsbXBox.hh"

using namespace idf;

UsbXBox::UsbXBox(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbXBox::update() {
    UsbDevice::update();

    unsigned char buffer[14];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        directionalPadUp.setValue(buffer[2] & 1);
        directionalPadDown.setValue(buffer[2] >> 1 & 1);
        directionalPadDown.setValue(buffer[2] >> 2 & 1);
        directionalPadDown.setValue(buffer[2] >> 3 & 1);

        startButton.setValue(buffer[2] >> 4 & 1);
        backButton.setValue(buffer[2] >> 5 & 1);
        leftAnalogIn.setValue(buffer[2] >> 6 & 1);
        rightAnalogIn.setValue(buffer[2] >> 7 & 1);

        leftBumper.setValue(buffer[3] & 1);
        rightBumper.setValue(buffer[3] >> 1 & 1);
        xBoxButton.setValue(buffer[3] >> 2 & 1);

        aButton.setValue(buffer[3] >> 4 & 1);
        bButton.setValue(buffer[3] >> 5 & 1);
        xButton.setValue(buffer[3] >> 6 & 1);
        yButton.setValue(buffer[3] >> 7 & 1);

        leftTrigger.setValue(buffer[4]);
        rightTrigger.setValue(buffer[5]);

        leftAnalogLeftRightPivot.setValue((int)(char)buffer[7] << 8 | buffer[6]);
        leftAnalogUpDownPivot.setValue((int)(char)buffer[9] << 8 | buffer[8]);

        rightAnalogLeftRightPivot.setValue((int)(char)buffer[11] << 8 | buffer[10]);
        rightAnalogUpDownPivot.setValue((int)(char)buffer[13] << 8 | buffer[12]);
    }
}
