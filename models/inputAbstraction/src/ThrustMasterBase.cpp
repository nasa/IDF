#include "ThrustMasterBase.hh"

using namespace idf;

#include <iostream>

ThrustMasterBase::ThrustMasterBase(bool isMale) :
    male(isMale),
    forwardBackwardPivot(72, 200),
    leftRightPivot(72, 200),
    twist(72, 200),
    forwardBackwardTranslation(0, 255),
    leftRightTranslation(72, 200),
    upDownTranslation(72, 200),
    trigger(0, 1) {}
