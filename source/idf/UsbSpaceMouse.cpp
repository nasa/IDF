#include "idf/UsbSpaceMouse.hh"

namespace idf {

UsbSpaceMouse::UsbSpaceMouse(int vendorID, int productID) :
    UsbSpaceBase("Space Mouse", vendorID, productID) {}

void UsbSpaceMouse::processButtons(const unsigned char* buttonData) {
    buttonMenu.setValue(buttonData[0] & 1);
    buttonFit.setValue(buttonData[0] >> 1 & 1);
    buttonT.setValue(buttonData[0] >> 2 & 1);
    buttonR.setValue(buttonData[0] >> 4 & 1);
    buttonF.setValue(buttonData[0] >> 5 & 1);

    buttonFlatRotation.setValue(buttonData[1] & 1);
    button1.setValue(buttonData[1] >> 4 & 1);
    button2.setValue(buttonData[1] >> 5 & 1);
    button3.setValue(buttonData[1] >> 6 & 1);
    button4.setValue(buttonData[1] >> 7 & 1);

    buttonEsc.setValue(buttonData[2] >> 6 & 1);
    buttonAlt.setValue(buttonData[2] >> 7 & 1);

    buttonShift.setValue(buttonData[3] & 1);
    buttonCtrl.setValue(buttonData[3] >> 1 & 1);
    buttonMouseRotation.setValue(buttonData[3] >> 2 & 1);
}

}
