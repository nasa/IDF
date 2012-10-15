#include "IndustrialProducts.hh"

using namespace idf;

IndustrialProducts::IndustrialProducts() :
        forwardBackwardPivot(0, 1023, 512),
        leftRightPivot(0, 1023, 512),
        twist(0, 255, 126),
        trigger(0, 1),
        hatNorth(0, 1),
        hatEast(0, 1),
        hatSouth(0, 1),
        hatWest(0, 1),
        threeStateSwitch(0, 2),
        hatUpDownPivot(0, 1023, 512),
        hatLeftRightPivot(0, 1023, 512) {}
