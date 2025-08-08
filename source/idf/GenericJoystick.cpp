#include "idf/GenericJoystick.hh"

namespace idf {

GenericJoystick::GenericJoystick() :
   forwardBackwardPivot(0, 1023, 512),
   leftRightPivot(0, 1023, 512),
   twist(0, 1023, 512),
   trigger(0,1),
   slider(0, 1023, 512) {
      buttons = {};
   }

const std::vector<InputLayout::Configurable>& GenericJoystick::getConfigurables() {
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
