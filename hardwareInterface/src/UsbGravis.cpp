#include "UsbGravis.hh"

using namespace idf;

UsbGravis::UsbGravis(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbGravis::update() {
    UsbDevice::update();

    unsigned char buffer[4];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        directionalPadLeft.setValue(~buffer[0] & 1);
        directionalPadRight.setValue(buffer[0] >> 7);

        directionalPadUp.setValue(~buffer[1] & 1);
        directionalPadDown.setValue(buffer[1] >> 7);

        westButton.setValue(buffer[2] & 1);
        southButton.setValue(buffer[2] >> 1 & 1);
        eastButton.setValue(buffer[2] >> 2 & 1);
        northButton.setValue(buffer[2] >> 3 & 1);

        leftBumper1.setValue(buffer[2] >> 4 & 1);
        rightBumper1.setValue(buffer[2] >> 5 & 1);
        leftBumper2.setValue(buffer[2] >> 6 & 1);
        rightBumper2.setValue(buffer[2] >> 7 & 1);

        selectButton.setValue(buffer[3] & 1);
        startButton.setValue(buffer[3] >> 1 & 1);
    }
}
