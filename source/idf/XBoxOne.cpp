#include "idf/XBoxOne.hh"

namespace idf {

XBoxOne::XBoxOne() :
    leftAnalogLeftRightPivot(0, 0xFFFF),
    leftAnalogUpDownPivot(0, 0xFFFF),
    leftAnalogTrigger(0, 0x3FF, 0),
    rightAnalogLeftRightPivot(0, 0xFFFF),
    rightAnalogUpDownPivot(0, 0xFFFF),
    rightAnalogTrigger(0, 0x3FF, 0),
    directionalPadUp(0, 1),
    directionalPadDown(0, 1),
    directionalPadLeft(0, 1),
    directionalPadRight(0, 1),
    viewButton(0, 1),
    xBoxButton(0, 1),
    menuButton(0, 1),
    xButton(0, 1),
    yButton(0, 1),
    aButton(0, 1),
    bButton(0, 1),
    leftBumper(0, 1),
    rightBumper(0, 1) {}

const std::vector<InputLayout::Configurable>& XBoxOne::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftAnalogLeftRightPivot, "Left Analog Left/Right Pivot", "leftAnalogLeftRightPivot"));
        inputs.push_back(Configurable(leftAnalogUpDownPivot, "Left Analog Up/Down Pivot", "leftAnalogUpDownPivot"));
        inputs.push_back(Configurable(leftAnalogTrigger, "Left Analog Trigger", "leftAnalogTrigger"));
        inputs.push_back(Configurable(rightAnalogLeftRightPivot, "Right Analog Left/Right Pivot", "rightAnalogLeftRightPivot"));
        inputs.push_back(Configurable(rightAnalogUpDownPivot, "Right Analog Up/Down Pivot", "rightAnalogUpDownPivot"));
        inputs.push_back(Configurable(rightAnalogTrigger, "Right Analog Trigger", "rightAnalogTrigger"));
    }
    return inputs;
}

}
