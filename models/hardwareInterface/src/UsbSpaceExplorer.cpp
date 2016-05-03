#include "hardwareInterface/include/UsbSpaceExplorer.hh"

using namespace idf;

UsbSpaceExplorer::UsbSpaceExplorer(int vendorID, int productID) :
    UsbSpaceBase("Space Explorer", vendorID, productID) {}

void UsbSpaceExplorer::processButtons(unsigned char* buttonData) {
    button1.setValue(buttonData[0] & 1);
    button2.setValue(buttonData[0] >> 1 & 1);
    buttonT.setValue(buttonData[0] >> 2 & 1);
    buttonL.setValue(buttonData[0] >> 3 & 1);
    buttonR.setValue(buttonData[0] >> 4 & 1);
    buttonF.setValue(buttonData[0] >> 5 & 1);
    buttonEsc.setValue(buttonData[0] >> 6 & 1);
    buttonAlt.setValue(buttonData[0] >> 7 & 1);
    buttonShift.setValue(buttonData[1] & 1);
    buttonCtrl.setValue(buttonData[1] >> 1 & 1);
    buttonFit.setValue(buttonData[1] >> 2 & 1);
    buttonPanel.setValue(buttonData[1] >> 3 & 1);
    buttonPlus.setValue(buttonData[1] >> 4 & 1);
    buttonMinus.setValue(buttonData[1] >> 5 & 1);
    button2d.setValue(buttonData[1] >> 6 & 1);
}
