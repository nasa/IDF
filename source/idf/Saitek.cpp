#include "idf/Saitek.hh"

namespace idf {

Saitek::Saitek() :
    leftPedal(0, 127),
    rightPedal(0, 127),
    twist(0, 511) {}

const std::vector<InputLayout::Configurable>& Saitek::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftPedal, "Left Pedal", "leftPedal"));
        inputs.push_back(Configurable(rightPedal, "Right Pedal", "rightPedal"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
    }
    return inputs;
}

}
