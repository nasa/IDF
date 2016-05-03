#include "inputAbstraction/include/ThrustMasterBase.hh"

using namespace idf;

ThrustMasterBase::ThrustMasterBase(bool isMale) :
    male(isMale),
    forwardBackwardPivot(72, 200),
    leftRightPivot(72, 200),
    twist(72, 200),
    forwardBackwardTranslation(0, 255),
    leftRightTranslation(72, 200),
    upDownTranslation(72, 200),
    trigger(-1, 1) {}

const std::vector<InputLayout::Configurable>& ThrustMasterBase::getConfigurables() {
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
