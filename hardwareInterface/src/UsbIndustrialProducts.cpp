#include "UsbIndustrialProducts.hh"

using namespace hardware;

UsbIndustrialProducts::UsbIndustrialProducts(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbIndustrialProducts::update() {
    UsbDevice::update();
}

void UsbIndustrialProducts::printState() {
}
