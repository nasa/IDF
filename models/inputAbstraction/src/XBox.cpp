#include "inputAbstraction/include/XBox.hh"

namespace idf {

XBox::XBox() :
    leftAnalogLeftRightPivot(-0x7FFF, 0x7FFF),
    leftAnalogUpDownPivot(-0x7FFF, 0x7FFF),
    leftAnalogIn(0, 1),
    rightAnalogLeftRightPivot(-0x7FFF, 0x7FFF),
    rightAnalogUpDownPivot(-0x7FFF, 0x7FFF),
    rightAnalogIn(0, 1),
    directionalPadUp(0, 1),
    directionalPadDown(0, 1),
    directionalPadLeft(0, 1),
    directionalPadRight(0, 1),
    backButton(0, 1),
    xBoxButton(0, 1),
    startButton(0, 1),
    xButton(0, 1),
    yButton(0, 1),
    aButton(0, 1),
    bButton(0, 1),
    leftBumper(0, 1),
    rightBumper(0, 1),
    leftTrigger(0, 1),
    rightTrigger(0, 1) {}

const std::vector<InputLayout::Configurable>& XBox::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftAnalogLeftRightPivot, "Left Analog Left/Right Pivot", "leftAnalogLeftRightPivot"));
        inputs.push_back(Configurable(leftAnalogUpDownPivot, "Left Analog Up/Down Pivot", "leftAnalogUpDownPivot"));
        inputs.push_back(Configurable(rightAnalogLeftRightPivot, "Right Analog Left/Right Pivot", "rightAnalogLeftRightPivot"));
        inputs.push_back(Configurable(rightAnalogUpDownPivot, "Right Analog Up/Down Pivot", "rightAnalogUpDownPivot"));
    }
    return inputs;
}

}
