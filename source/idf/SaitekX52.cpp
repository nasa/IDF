#include "idf/SaitekX52.hh"

namespace idf {

SaitekX52::SaitekX52() : 
    forwardBackwardPivot(0, 2047, 1023),
    leftRightPivot(0, 2047, 1023),
    twist(0, 1023, 511),
    trigger(0, 1),
    triggerStage2(0, 1),
    trigger2(0, 1),
    buttonFire(0, 1),
    buttonA(0, 1),
    buttonB(0, 1),
    buttonC(0, 1),
    buttonD(0, 1),
    buttonE(0, 1),
    buttonI(0, 1),
    toggle1(-1, 1),
    toggle2(-1, 1),
    toggle3(-1, 1),
    toggle4(-1, 1),
    toggle5(-1, 1),
    toggle6(-1, 1),
    hat1North(0,1),
    hat1NorthEast(0,1),
    hat1East(0,1),
    hat1SouthEast(0,1),
    hat1South(0,1),
    hat1SouthWest(0,1),
    hat1West(0,1),
    hat1NorthWest(0,1),
    hat2North(0,1),
    hat2NorthEast(0,1),
    hat2East(0,1),
    hat2SouthEast(0,1),
    hat2South(0,1),
    hat2SouthWest(0,1),
    hat2West(0,1),
    hat2NorthWest(0,1),
    hat3North(0,1),
    hat3NorthEast(0,1),
    hat3East(0,1),
    hat3SouthEast(0,1),
    hat3South(0,1),
    hat3SouthWest(0,1),
    hat3West(0,1),
    hat3NorthWest(0,1),
    mode(1,3),
    throttle(0, 255),
    scrollUp(0,1),
    scrollDown(0,1),
    rotary1(0, 255, 127),
    rotary2(0, 255, 127),
    mouseLeftClick(0, 1),
    thumbForwardBackwardPivot(0, 15, 8),
    thumbUpDownPivot(0, 15, 8),
    slider(0, 255),
    buttonFunction(0, 1),
    buttonStartStop(0, 1),
    buttonReset(0, 1)
    {}

const std::vector<InputLayout::Configurable>& SaitekX52::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));

        inputs.push_back(Configurable(throttle, "Throttle", "throttle"));
        inputs.push_back(Configurable(thumbForwardBackwardPivot, "Thumb Forward Backward Pivot", "thumbForwardBackwardPivot"));
        inputs.push_back(Configurable(thumbUpDownPivot, "Thumb Up Down Pivot", "thumbUpdDownPivot"));
        inputs.push_back(Configurable(slider, "Slider", "slider"));
    }
    return inputs;
}

}
