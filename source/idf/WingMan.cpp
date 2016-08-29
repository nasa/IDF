#include "idf/WingMan.hh"

namespace idf {

WingMan::WingMan() :
    forwardBackwardPivot(0, 1023, 512),
    leftRightPivot(0, 1023, 512),
    twist(0, 255, 126),
    trigger(0, 1),
    button2(0, 1),
    button3(0, 1),
    button4(0, 1),
    button5(0, 1),
    button6(0, 1),
    button7(0, 1),
    hatNorth(0, 1),
    hatNorthEast(0, 1),
    hatEast(0, 1),
    hatSouthEast(0, 1),
    hatSouth(0, 1),
    hatSouthWest(0, 1),
    hatWest(0, 1),
    hatNorthWest(0, 1),
    slider(0, 255, 127) {}

const std::vector<InputLayout::Configurable>& WingMan::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
        inputs.push_back(Configurable(slider, "Slider", "slider"));
    }
    return inputs;
}

}
