#include "idf/SerialEr7Orion.hh"

#include <stdio.h>
namespace idf {

SerialEr7Orion::SerialEr7Orion(const char *terminalPath) :
    ThrustMasterBase(false),
    SerialThrustMasterBase("ER7 Orion", terminalPath, false),
    Er7Orion() {}

void SerialEr7Orion::decode(const std::vector<unsigned char>& data) {
    SerialThrustMasterBase::decode(data);
    forwardBackwardTranslation.setValue(data[3]);
    leftRightTranslation.setValue(data[4]);
    upDownTranslation.setValue(data[5]);
}

void SerialEr7Orion::processButtons(unsigned char buttonByte) {
    cfsButton.setValue(   (buttonByte >> 3) & 1);
    bfsButton.setValue(   (buttonByte >> 2) & 1);
    rhcButton.setValue(   (buttonByte >> 4) & 1);
    abortButton.setValue( (buttonByte >> 7) & 1);
    trigger.setValue(     (buttonByte >> 0) & 1);
    thcButton.setValue(   (buttonByte >> 5) & 1);
}

}
