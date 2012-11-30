#include "UsbWingMan.hh"

using namespace idf;

UsbWingMan::UsbWingMan(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbWingMan::update() {
    UsbDevice::update();

    unsigned char buffer[6];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        leftRightPivot.setValue(((unsigned)buffer[1] & 3) << 8 | buffer[0]);
        forwardBackwardPivot.setValue(((unsigned)buffer[2] & 0xF) << 6 | buffer[1] >> 2);
        twist.setValue(buffer[3]);

        trigger.setValue(buffer[4] & 1);
        button2.setValue(buffer[4] >> 1 & 1);
        button3.setValue(buffer[4] >> 2 & 1);
        button4.setValue(buffer[4] >> 3 & 1);
        button5.setValue(buffer[4] >> 4 & 1);
        button6.setValue(buffer[4] >> 5 & 1);
        button7.setValue(buffer[4] >> 6 & 1);

        unsigned int hat = buffer[2] >> 4;

        hatNorth.setValue(hat == 0);
        hatNorthEast.setValue(hat == 1);
        hatEast.setValue(hat == 2);
        hatSouthEast.setValue(hat == 3);
        hatSouth.setValue(hat == 4);
        hatSouthWest.setValue(hat == 5);
        hatWest.setValue(hat == 6);
        hatNorthWest.setValue(hat == 7);

        slider.setValue(buffer[5]);
    }
}
