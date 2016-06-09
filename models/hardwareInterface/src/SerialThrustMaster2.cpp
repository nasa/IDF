#include "hardwareInterface/include/SerialThrustMaster2.hh"

namespace idf {

SerialThrustMaster2::SerialThrustMaster2(const char *terminalPath, bool isMale) :
    ThrustMasterBase(isMale),
    SerialThrustMasterBase("Orion Style Thrust Master", terminalPath, isMale),
    ThrustMaster2(isMale) {}

void SerialThrustMaster2::processButtons(unsigned char buttonByte) {
    leftButton.setValue(buttonByte >> 1 & 1);
    middleButton.setValue(buttonByte >> 2 & 1);
    rightButton.setValue(buttonByte >> 3 & 1);
}

}
