#include "hardwareInterface/include/SerialThrustMaster.hh"

namespace idf {

SerialThrustMaster::SerialThrustMaster(const char *terminalPath, bool isMale) :
    ThrustMasterBase(isMale),
    SerialThrustMasterBase("Shuttle Style Thrust Master", terminalPath, isMale),
    ThrustMaster(isMale) {}

void SerialThrustMaster::processButtons(unsigned char buttonByte) {
    topSwitch.setValue(buttonByte >> 2 & 1);
    topButton.setValue(buttonByte >> 3 & 1);
    leftSwitch.setValue(buttonByte & 16 ? 1 : buttonByte &  32 ? -1 : 0);
    rightSwitch.setValue(buttonByte & 64 ? 1 : buttonByte & 128 ? -1 : 0);
}

}
