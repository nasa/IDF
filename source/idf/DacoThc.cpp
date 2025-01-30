#include "idf/DacoThc.hh"

namespace idf {

DacoThc::DacoThc() :
   forwardBackwardTranslation(0, 65535, 32768),
   leftRightTranslation(0, 65535, 32768),
   upDownTranslation(0, 65535, 32768),
   switch1(0, 1) {}

const std::vector<InputLayout::Configurable>& DacoThc::getConfigurables() {
   static std::vector<Configurable> inputs;
   if (inputs.empty()) {
      append(InputLayout::getConfigurables(), inputs);
      inputs.push_back(Configurable(forwardBackwardTranslation, "Forward/Backward Translation", "forwardBackwardTranslation"));
      inputs.push_back(Configurable(leftRightTranslation, "Left/Right Translation", "leftRightTranslation"));
      inputs.push_back(Configurable(upDownTranslation, "Up/Down Translation", "upDownTranslation"));
   }
   return inputs;
}

} // namespace idf