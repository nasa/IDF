#include "idf/T16000M.hh"

namespace idf {

T16000M::T16000M() :
   forwardBackwardPivot(0, 16383),
   leftRightPivot(0, 16383),
   twist(0, 255),
   trigger(0, 1),
   middleButton(0, 1),
   leftButton(0, 1),
   rightButton(0, 1),
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
   hatNorth(0, 1),
   hatNorthEast(0, 1),
   hatEast(0, 1),
   hatSouthEast(0, 1),
   hatSouth(0, 1),
   hatSouthWest(0, 1),
   hatWest(0, 1),
   hatNorthWest(0, 1),
   slider(0, 255),
   rightHandMode(0, 1)
{}

void T16000M::setForceRightHandedMode(bool force) {
    forceRightHanded = force;
}

bool T16000M::getForceRightHandedMode() {
    return forceRightHanded;
}

const std::vector<InputLayout::Configurable>& T16000M::getConfigurables() {
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

} // namespace idf