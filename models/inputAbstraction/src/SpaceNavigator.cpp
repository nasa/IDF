#include "SpaceNavigator.hh"

using namespace idf;

SpaceNavigator::SpaceNavigator() :
    forwardBackwardPivot(-350, 350, 0),
    leftRightPivot(-350, 350, 0),
    twist(-350, 350, 0),
    forwardBackwardTranslation(-350, 350, 0),
    leftRightTranslation(-350, 350, 0),
    upDownTranslation(-350, 350, 0),
    leftButton(0, 1),
    rightButton(0, 1) {}
