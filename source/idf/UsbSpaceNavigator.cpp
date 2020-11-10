#include "idf/UsbSpaceNavigator.hh"

namespace idf {

UsbSpaceNavigator::UsbSpaceNavigator() :
    UsbSpaceBase("Space Navigator") {}

void UsbSpaceNavigator::processButtons(const unsigned char* buttonData) {
    leftButton.setValue(buttonData[0] & 1);
    rightButton.setValue(buttonData[0] >> 1 & 1);
}

}
