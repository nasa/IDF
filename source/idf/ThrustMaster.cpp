#include "idf/ThrustMaster.hh"

namespace idf {

ThrustMaster::ThrustMaster(bool isMale) :
    ThrustMasterBase(isMale),
    topSwitch(0, 1),
    topButton(0, 1),
    leftSwitch(-1, 1),
    rightSwitch(-1, 1) {}

}
