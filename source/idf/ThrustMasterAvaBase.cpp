#include "idf/ThrustMasterAvaBase.hh"

namespace idf {

ThrustMasterAvaBase::ThrustMasterAvaBase() :
    forwardBackwardPivot(0, 65535, 32768),
    leftRightPivot(0, 65535, 32768),
    twist(0, 65535, 32768),
    forwardBackwardThumbstickPivot(0, 65535, 32768),
    leftRightThumbstickPivot(0, 65535, 32768),
    rotationZ(0, 65535, 32768),
    hatNorth(0, 1),
    hatNorthEast(0, 1),
    hatEast(0, 1),
    hatSouthEast(0, 1),
    hatSouth(0, 1),
    hatSouthWest(0, 1),
    hatWest(0, 1),
    hatNorthWest(0, 1),
    slider(0, 255),
    dial(0,255),
    trigger(0, 1),
    button2(0, 1),
    button3(0, 1),
    button4(0, 1),
    button5(0, 1),
    button6(0, 1),
    button7(0, 1),
    button8(0, 1),
    button9(0, 1),
    button10(0, 1),
    button11(0, 1),
    button12(0, 1),
    button13(0, 1),
    button14(0, 1),
    button15(0, 1),
    button16(0, 1),
    button17(0, 1),
    button18(0, 1),
    button19(0, 1),
    button20(0, 1),
    button21(0, 1),
    button22(0, 1),
    button23(0, 1),
    button24(0, 1),
    button25(0, 1),
    button26(0, 1),
    button27(0, 1),
    button28(0, 1),
    button29(0, 1),
    button30(0, 1),
    button31(0, 1),
    button32(0, 1) {}

const std::vector<InputLayout::Configurable>& ThrustMasterAvaBase::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "forwardBackwardPivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "leftRightPivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "twist", "twist"));
        inputs.push_back(Configurable(forwardBackwardThumbstickPivot, "forwardBackwardThumbstickPivot", "forwardBackwardThumbstickPivot"));
        inputs.push_back(Configurable(leftRightThumbstickPivot, "leftRightThumbstickPivot", "leftRightThumbstickPivot"));
        inputs.push_back(Configurable(rotationZ, "rotationZ", "rotationZ"));
        inputs.push_back(Configurable(slider, "slider", "slider"));
        inputs.push_back(Configurable(dial, "dial", "dial"));
    }
    return inputs;
}

} // namespace idf
