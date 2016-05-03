#include "hardwareInterface/include/UsbSaitek.hh"

using namespace idf;

UsbSaitek::UsbSaitek(int vendorID, int productID) :
    UsbDevice("Saitek", vendorID, productID) {}

void UsbSaitek::update() {
    UsbDevice::update();

    unsigned char buffer[3];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        leftPedal.setValue(buffer[0] & 0x7F);
        rightPedal.setValue(((buffer[1] << 1) & 0x7F) | (buffer[0] >> 7));
        twist.setValue((int)(char)buffer[2] << 2 | (buffer[1] >> 6));
    }
}
