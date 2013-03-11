#include "SerialThrustMaster.hh"

using namespace idf;

#include <iostream>

SerialThrustMaster::SerialThrustMaster(const char *terminalPath, bool isMale) :
    SerialThrustMasterBase(terminalPath, isMale) {
    std::cout << "SerialThrustMaster isMale = " << isMale << std::endl;
}

void SerialThrustMaster::processButtons(unsigned char buttonByte) {
    topSwitch.setValue(buttonByte >> 2 & 1);
    topButton.setValue(buttonByte >> 3 & 1);
}
