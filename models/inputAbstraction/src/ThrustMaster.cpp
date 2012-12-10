#include "ThrustMaster.hh"

using namespace idf;

ThrustMaster::ThrustMaster() :
    forwardBackwardPivot(0, 255),
    leftRightPivot(0, 255),
    twist(0, 255),
    forwardBackwardTranslation(0, 255),
    leftRightTranslation(0, 255),
    upDownTranslation(0, 255),
    leftButton(0, 1),
    middleButton(0, 1),
    rightButton(0, 1),
    trigger(0, 1) {}
