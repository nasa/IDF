#include "hardwareInterface/include/UsbWingMan.hh"

using namespace idf;

UsbWingMan::UsbWingMan(int vendorID, int productID, const std::string& id) :
    UsbDevice(id, vendorID, productID),
    byteCount(6) {}

UsbWingMan::UsbWingMan(int vendorID, int productID, const std::string& id, int numBytes) :
    UsbDevice(id, vendorID, productID),
    byteCount(numBytes) {}

void UsbWingMan::update() {
    UsbDevice::update();

    unsigned char buffer[byteCount];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        processData(buffer);
    }
}

void UsbWingMan::processData(unsigned char *data) {
    leftRightPivot.setValue(((unsigned)data[1] & 3) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[2] & 0xF) << 6 | data[1] >> 2);
    twist.setValue(data[3]);

    trigger.setValue(data[4] & 1);
    button2.setValue(data[4] >> 1 & 1);
    button3.setValue(data[4] >> 2 & 1);
    button4.setValue(data[4] >> 3 & 1);
    button5.setValue(data[4] >> 4 & 1);
    button6.setValue(data[4] >> 5 & 1);
    button7.setValue(data[4] >> 6 & 1);

    unsigned int hat = data[2] >> 4;

    hatNorth.setValue(hat == 0);
    hatNorthEast.setValue(hat == 1);
    hatEast.setValue(hat == 2);
    hatSouthEast.setValue(hat == 3);
    hatSouth.setValue(hat == 4);
    hatSouthWest.setValue(hat == 5);
    hatWest.setValue(hat == 6);
    hatNorthWest.setValue(hat == 7);

    slider.setValue(data[5]);
}
