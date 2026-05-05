#include "idf/GenericJoystick.hh"
#include <iostream>

namespace idf {


GenericJoystick::GenericJoystick() :
   forwardBackwardPivot(0, 1023, 512),
   leftRightPivot(0, 1023, 512),
   forwardBackwardTranslation(0, 1023, 512),
   leftRightTranslation(0, 1024, 512),
   twist(0, 1023, 512),
   trigger(0,1),
   slider(0, 1023, 512),
   wheel(0, 127, 64),
   HatNorth(0,1),
   HatNorthEast(0,1),
   HatEast(0,1),
   HatSouthEast(0,1),
   HatSouth(0,1),
   HatSouthWest(0,1),
   HatWest(0,1),
   HatNorthWest(0,1) {
      buttons = {};
   }

const SingleInput* GenericJoystick::getButton(const int number) {
   try {
      return buttons.at(number-1);
   }
   catch (const std::out_of_range& e) {
      return NULL;
   }
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
