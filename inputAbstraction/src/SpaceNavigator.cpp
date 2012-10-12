#include "SpaceNavigator.hh"

using namespace hardware;

SpaceNavigator::SpaceNavigator() :
    forwardBackwardPivot(-512, 511, 0),
    leftRightPivot(-512, 511, 0),
    twist(-512, 511, 0),
    forwardBackwardTranslation(-512, 511, 0),
    leftRightTranslation(-512, 511, 0),
    upDownTranslation(-512, 511, 0) {}
