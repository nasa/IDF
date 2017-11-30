#include "idf/IndustrialProducts2.hh"

namespace idf {

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

const std::vector<InputLayout::Configurable>& IndustrialProducts2::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
    }
    return inputs;
}

}
