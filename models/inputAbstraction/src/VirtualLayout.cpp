#include "inputAbstraction/include/VirtualLayout.hh"

namespace idf {

VirtualLayout::VirtualLayout() :
    leftRightRotation(-100, 100),
    upDownRotation(-100, 100),
    clockwiseCounterclockwiseRotation(-100, 100),
    leftRightTranslation(-100, 100),
    upDownTranslation(-100, 100),
    inOutTranslation(-100, 100) {}

}
