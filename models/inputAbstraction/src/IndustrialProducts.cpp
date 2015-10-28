#include "inputAbstraction/include/IndustrialProducts.hh"

using namespace idf;

IndustrialProducts::IndustrialProducts() :
    forwardBackwardPivot(0, 1023, 512),
    leftRightPivot(0, 1023, 512),
    twist(0, 1023, 512),
    trigger(0, 1),
    hatNorth(0, 1),
    hatEast(0, 1),
    hatSouth(0, 1),
    hatWest(0, 1),
    switchUp(0, 1),
    switchDown(0, 1),
    hatUpDownPivot(0, 1023, 512),
    hatLeftRightPivot(0, 1023, 512) {}
