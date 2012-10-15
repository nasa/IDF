#include "UsbSpaceNavigator.hh"

using namespace idf;

UsbSpaceNavigator::UsbSpaceNavigator(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbSpaceNavigator::update() {
    UsbDevice::update();

    int bytesRead;
    do {
        unsigned char buffer[7];
        bytesRead = hid_read(hidDevice, buffer, sizeof(buffer));

        if (bytesRead == 7) {

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
            }
        }
        else if (bytesRead < 0) {
            mOpen = false;
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
                << "Error while updating.";
            throw IOException(oss.str().c_str());
        }
    } while (bytesRead > 0);
}

void UsbSpaceNavigator::printState() {
    std::cout << "F/B Pivot" << forwardBackwardPivot.toString()
              << "L/R Pivot" << leftRightPivot.toString()
              << "Twist" << twist.toString()
              << "F/B Trans" << forwardBackwardTranslation.toString()
              << "L/R Trans" << leftRightTranslation.toString()
              << "U/D Trans" << upDownTranslation.toString()
              << std::endl;
}
