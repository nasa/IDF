#include "UsbSpaceExplorer.hh"

using namespace idf;

UsbSpaceExplorer::UsbSpaceExplorer(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbSpaceExplorer::update() {
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

    } while (bytesRead > 0);
}
