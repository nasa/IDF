#include "inputAbstraction/include/ChProPedals.hh"

using namespace idf;

ChProPedals::ChProPedals() :
    leftPedal(0, 255),
    rightPedal(0, 255),
    twist(0, 255) {}

const std::vector<InputLayout::Configurable>& ChProPedals::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftPedal, "Left Pedal", "leftPedal"));
        inputs.push_back(Configurable(rightPedal, "Right Pedal", "rightPedal"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
    }
    return inputs;
}
