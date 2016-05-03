#include "hardwareInterface/include/UsbSpaceNavigator.hh"

using namespace idf;

UsbSpaceNavigator::UsbSpaceNavigator(int vendorID, int productID) :
    UsbSpaceBase("Space Navigator", vendorID, productID) {
    productIds.push_back(0xC626);
}

void UsbSpaceNavigator::processButtons(unsigned char* buttonData) {
    leftButton.setValue(buttonData[0] & 1);
    rightButton.setValue(buttonData[0] >> 1 & 1);
}
