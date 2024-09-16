#include "idf/IndustrialProducts4.hh"

namespace idf {

IndustrialProducts4::IndustrialProducts4() :
    forwardBackwardPivot(0, 1023, 512),
    leftRightPivot(0, 1023, 512),
    twist(0, 1023, 512),
    trigger(0, 1),
    grip(0,1),
    switchUp(0, 1),
    switchDown(0, 1),
    hatUpDownPivot(0, 1023, 512),
    hatLeftRightPivot(0, 1023, 512),
    button1(0, 1),
    button2(0, 1) {}

const std::vector<InputLayout::Configurable>& IndustrialProducts4::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
        inputs.push_back(Configurable(hatUpDownPivot, "Hat Up/Down Pivot", "hatUpDownPivot"));
        inputs.push_back(Configurable(hatLeftRightPivot, "Hat Left/Right Pivot", "hatLeftRightPivot"));
    }
    return inputs;
}

}
