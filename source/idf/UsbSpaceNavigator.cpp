#include "idf/UsbSpaceNavigator.hh"

namespace idf {

UsbSpaceNavigator::UsbSpaceNavigator(int vendorID, int productID) :
    UsbSpaceBase("Space Navigator", vendorID, productID) {
    productIds.push_back(0xC626);
}

void UsbSpaceNavigator::processButtons(const unsigned char* buttonData) {
    leftButton.setValue(buttonData[0] & 1);
    rightButton.setValue(buttonData[0] >> 1 & 1);
}

}
