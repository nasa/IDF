#include "idf/Daco.hh"

namespace idf {

Daco::Daco() :
   x(0, 65535, 32768),
   y(0, 65535, 32768),
   z(0, 65535, 32768),
   switch1(0, 1) {}

const std::vector<InputLayout::Configurable>& Daco::getConfigurables() {
   static std::vector<Configurable> inputs;
   if (inputs.empty()) {
      append(InputLayout::getConfigurables(), inputs);
      inputs.push_back(Configurable(x, "X", "x"));
      inputs.push_back(Configurable(y, "Y", "y"));
      inputs.push_back(Configurable(z, "Z", "z"));
   }
   return inputs;
}

} // namespace idf