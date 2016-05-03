#include "inputAbstraction/include/DualShock.hh"

using namespace idf;

DualShock::DualShock() :
    leftAnalogLeftRightPivot(0, 255),
    leftAnalogUpDownPivot(0, 255),
    leftAnalogIn(0, 1),
    rightAnalogLeftRightPivot(0, 255),
    rightAnalogUpDownPivot(0, 255),
    rightAnalogIn(0, 1),
    directionalPadUp(0, 1),
    directionalPadDown(0, 1),
    directionalPadLeft(0, 1),
    directionalPadRight(0, 1),
    squareButton(0, 1),
    triangleButton(0, 1),
    xButton(0, 1),
    circleButton(0, 1),
    psButton(0, 1),
    leftBumper(0, 1),
    rightBumper(0, 1),
    leftTrigger(0, 255),
    rightTrigger(0, 255) {}

const std::vector<InputLayout::Configurable>& DualShock::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftAnalogLeftRightPivot, "Left Analog Left/Right Pivot", "leftAnalogLeftRightPivot"));
        inputs.push_back(Configurable(leftAnalogUpDownPivot, "Left Analog Up/Down Pivot", "leftAnalogUpDownPivot"));
        inputs.push_back(Configurable(rightAnalogLeftRightPivot, "Right Analog Left/Right Pivot", "rightAnalogLeftRightPivot"));
        inputs.push_back(Configurable(rightAnalogUpDownPivot, "Right Analog Up/Down Pivot", "rightAnalogUpDownPivot"));
        inputs.push_back(Configurable(leftTrigger, "Left Trigger", "leftTrigger"));
        inputs.push_back(Configurable(rightTrigger, "Right Trigger", "rightTrigger"));
    }
    return inputs;
}

void DualShock::silenceRumblers() {
    rumble(Weak, 0);
    rumble(Strong, 0);
}
