#include "SerialThrustMaster.hh"

using namespace idf;

SerialThrustMaster::SerialThrustMaster(const char *terminalPath, bool isMale) :
    ThrustMasterBase(isMale),
    SerialThrustMasterBase(terminalPath, isMale),
    ThrustMaster(isMale) {}

void SerialThrustMaster::processButtons(unsigned char buttonByte) {
    topSwitch.setValue(buttonByte >> 2 & 1);
    topButton.setValue(buttonByte >> 3 & 1);
}
