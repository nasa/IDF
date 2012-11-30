#include "UsbDualShock3.hh"

using namespace idf;

UsbDualShock3::UsbDualShock3(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbDualShock3::update() {
    UsbDevice::update();

    unsigned char buffer[49];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        selectButton.setValue(buffer[2] & 1);
        leftAnalogIn.setValue(buffer[2] >> 1 & 1);
        rightAnalogIn.setValue(buffer[2] >> 2 & 1);
        startButton.setValue(buffer[2] >> 3 & 1);

        playStationButton.setValue(buffer[4] & 1);

        leftAnalogLeftRightPivot.setValue(buffer[6]);
        leftAnalogUpDownPivot.setValue(buffer[7]);
        rightAnalogLeftRightPivot.setValue(buffer[8]);
        rightAnalogUpDownPivot.setValue(buffer[9]);

        directionalPadUp.setValue(buffer[14]);
        directionalPadRight.setValue(buffer[15]);
        directionalPadDown.setValue(buffer[16]);
        directionalPadLeft.setValue(buffer[17]);

        leftTrigger.setValue(buffer[18]);
        rightTrigger.setValue(buffer[19]);
        leftBumper.setValue(buffer[20]);
        rightBumper.setValue(buffer[21]);

        triangleButton.setValue(buffer[22]);
        circleButton.setValue(buffer[23]);
        xButton.setValue(buffer[24]);
        squareButton.setValue(buffer[25]);
    }
}
