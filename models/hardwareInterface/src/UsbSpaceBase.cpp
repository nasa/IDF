#include "UsbSpaceBase.hh"

using namespace idf;

UsbSpaceBase::UsbSpaceBase(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbSpaceBase::update() {
    UsbDevice::update();

    int bytesRead;
    do {
        unsigned char buffer[7];
        bytesRead = read(buffer, sizeof(buffer));

        if (bytesRead) {
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
                    processButtons(&buffer[1]);
                    break;
            }
        }

    } while (bytesRead > 0);
}
