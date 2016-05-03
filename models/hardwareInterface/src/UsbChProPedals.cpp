#include "hardwareInterface/include/UsbChProPedals.hh"

using namespace idf;

UsbChProPedals::UsbChProPedals(int vendorID, int productID) :
    UsbDevice("Ch Pro Pedals", vendorID, productID) {}

void UsbChProPedals::update() {
    UsbDevice::update();

    unsigned char buffer[3];
    int bytesRead;
    bool dataReceived = false;

    do {
        dataReceived |= bytesRead = read(buffer, sizeof(buffer));
    } while (bytesRead > 0);

    if (dataReceived) {
        leftPedal.setValue(buffer[0]);
        rightPedal.setValue(buffer[1]);
        twist.setValue(buffer[2]);
    }
}
