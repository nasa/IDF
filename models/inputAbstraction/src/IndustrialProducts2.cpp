#include "inputAbstraction/include/IndustrialProducts2.hh"

using namespace idf;

IndustrialProducts2::IndustrialProducts2() :
    forwardBackwardPivot(0, 1023, 512),
    leftRightPivot(0, 1023, 512),
    twist(0, 1023, 512),
    trigger(0, 1),
    hatNorth(0, 1),
    hatEast(0, 1),
    hatSouth(0, 1),
    hatWest(0, 1),
    northWestButton(0, 1),
    southWestButton(0, 1),
    northEastButton(0, 1),
    southEastButton(0, 1) {}
