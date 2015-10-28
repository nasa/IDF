#include "inputAbstraction/include/SpaceBase.hh"

using namespace idf;

SpaceBase::SpaceBase() :
    forwardBackwardPivot(-350, 350, 0),
    leftRightPivot(-350, 350, 0),
    twist(-350, 350, 0),
    forwardBackwardTranslation(-350, 350, 0),
    leftRightTranslation(-350, 350, 0),
    upDownTranslation(-350, 350, 0) {}
