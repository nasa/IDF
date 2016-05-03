#include "hardwareInterface/include/UsbIndustrialProducts.hh"

using namespace idf;

UsbIndustrialProducts::UsbIndustrialProducts(int vendorID, int productID) :
    UsbDevice("Industrial Products", vendorID, productID) {
    productIds.push_back(0x0019);
}

void UsbIndustrialProducts::update() {
    UsbDevice::update();

    unsigned char buffer[8];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        leftRightPivot.setValue(((unsigned)buffer[1]) << 8 | buffer[0]);
        forwardBackwardPivot.setValue(((unsigned)buffer[3]) << 8 | buffer[2]);
        twist.setValue(((unsigned)buffer[5]) << 8 | buffer[4]);

        trigger.setValue(buffer[6] & 1);

        southWestButton.setValue(buffer[6] >> 1 & 1);
        northWestButton.setValue(buffer[6] >> 2 & 1);
        northEastButton.setValue(buffer[6] >> 3 & 1);
        southEastButton.setValue(buffer[7] & 1);

        hatNorth.setValue(buffer[6] >> 4 & 1);
        hatEast.setValue(buffer[6] >> 5 & 1);
        hatSouth.setValue(buffer[6] >> 6 & 1);
        hatWest.setValue(buffer[6] >> 7 & 1);
    }
}
