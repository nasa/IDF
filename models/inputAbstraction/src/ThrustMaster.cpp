#include "ThrustMaster.hh"

using namespace idf;

ThrustMaster::ThrustMaster(bool isMale) :
    male(isMale),
    forwardBackwardPivot(72, 200),
    leftRightPivot(72, 200),
    twist(72, 200),
    forwardBackwardTranslation(0, 255),
    leftRightTranslation(72, 200),
    upDownTranslation(72, 200),
    leftButton(0, 1),
    middleButton(0, 1),
    rightButton(0, 1),
    trigger(0, 1) {}
