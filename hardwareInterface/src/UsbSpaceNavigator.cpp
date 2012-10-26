#include "UsbSpaceNavigator.hh"

using namespace idf;

UsbSpaceNavigator::UsbSpaceNavigator(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbSpaceNavigator::update() {
    UsbDevice::update();

    int bytesRead;
    do {
        unsigned char buffer[7];
        bytesRead = read(buffer, sizeof(buffer));

        switch (buffer[0]) {
            case 1:
                leftRightTranslation.setValue((int)(char)buffer[2] << 8 | buffer[1]);
                forwardBackwardTranslation.setValue((int)(char)buffer[4] << 8 | buffer[3]);
                upDownTranslation.setValue((int)(char)buffer[6] << 8 | buffer[5]);
                break;
            case 2:
                forwardBackwardPivot.setValue((int)(char)buffer[2] << 8 | buffer[1]);
                leftRightPivot.setValue((int)(char)buffer[4] << 8 | buffer[3]);
                twist.setValue((int)(char)buffer[6] << 8 | buffer[5]);
                break;
            case 3:
                leftButton.setValue(buffer[1] & 1);
                rightButton.setValue(buffer[1] >> 1 & 1);
                break;
        }

    } while (bytesRead > 0);
}
