#include "inputAbstraction/include/SpaceBase.hh"

using namespace idf;

SpaceBase::SpaceBase() :
    forwardBackwardPivot(-350, 350, 0),
    leftRightPivot(-350, 350, 0),
    twist(-350, 350, 0),
    forwardBackwardTranslation(-350, 350, 0),
    leftRightTranslation(-350, 350, 0),
    upDownTranslation(-350, 350, 0) {}

const std::vector<InputLayout::Configurable>& SpaceBase::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
        inputs.push_back(Configurable(forwardBackwardTranslation, "Forward/Backward Translation", "forwardBackwardTranslation"));
        inputs.push_back(Configurable(leftRightTranslation, "Left/Right Translation", "leftRightTranslation"));
        inputs.push_back(Configurable(upDownTranslation, "Up/Down Translation", "upDownTranslation"));
    }
    return inputs;
}
