#include "UsbSpaceExplorer.hh"

using namespace idf;

UsbSpaceExplorer::UsbSpaceExplorer(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbSpaceExplorer::update() {
    UsbDevice::update();

    int bytesRead;
    do {
        unsigned char buffer[7];
        bytesRead = hid_read(hidDevice, buffer, sizeof(buffer));

        if (bytesRead == 3 || bytesRead == 7) {

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
                    button1.setValue(buffer[1] & 1);
                    button2.setValue(buffer[1] >> 1 & 1);
                    buttonT.setValue(buffer[1] >> 2 & 1);
                    buttonL.setValue(buffer[1] >> 3 & 1);
                    buttonR.setValue(buffer[1] >> 4 & 1);
                    buttonF.setValue(buffer[1] >> 5 & 1);
                    buttonEsc.setValue(buffer[1] >> 6 & 1);
                    buttonAlt.setValue(buffer[1] >> 7 & 1);
                    buttonShift.setValue(buffer[2] & 1);
                    buttonCtrl.setValue(buffer[2] >> 1 & 1);
                    buttonFit.setValue(buffer[2] >> 2 & 1);
                    buttonPanel.setValue(buffer[2] >> 3 & 1);
                    buttonPlus.setValue(buffer[2] >> 4 & 1);
                    buttonMinus.setValue(buffer[2] >> 5 & 1);
                    button2d.setValue(buffer[2] >> 6 & 1);
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

void UsbSpaceExplorer::printState() {
    std::cout << "F/B Pivot" << forwardBackwardPivot.toString()
              << "L/R Pivot" << leftRightPivot.toString()
              << "Twist" << twist.toString()
              << "F/B Trans" << forwardBackwardTranslation.toString()
              << "L/R Trans" << leftRightTranslation.toString()
              << "U/D Trans" << upDownTranslation.toString()
              << "b1" << button1.toString()
              << "b2" << button2.toString()
              << "-" << buttonMinus.toString()
              << "+" << buttonPlus.toString()
              << "ESC" << buttonEsc.toString()
              << "CTRL" << buttonCtrl.toString()
              << "ALT" << buttonAlt.toString()
              << "SHIFT" << buttonShift.toString()
              << "T" << buttonT.toString()
              << "L" << buttonL.toString()
              << "R" << buttonR.toString()
              << "2D" << button2d.toString()
              << "F" << buttonF.toString()
              << "PANEL" << buttonPanel.toString()
              << "FIT" << buttonFit.toString()
              << std::endl;
}
