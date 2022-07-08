#include "idf/SaitekX56Throttle.hh"

namespace idf {

SaitekX56Throttle::SaitekX56Throttle() :
    leftThrottle(0, 1023, 511),
    rightThrottle(0, 1023, 511),
    buttonE(0, 1),
    buttonF(0, 1),
    buttonG(0, 1),
    buttonH(0, 1),
    buttonI(0, 1),
    buttonJ(0, 1),
    buttonK(0, 1),
    buttonL(0, 1),
    hat3North(0,1),
    hat3NorthEast(0,1),
    hat3East(0,1),
    hat3SouthEast(0,1),
    hat3South(0,1),
    hat3SouthWest(0,1),
    hat3West(0,1),
    hat3NorthWest(0,1),
    hat4North(0,1),
    hat4NorthEast(0,1),
    hat4East(0,1),
    hat4SouthEast(0,1),
    hat4South(0,1),
    hat4SouthWest(0,1),
    hat4West(0,1),
    hat4NorthWest(0,1),
    mode(1,3),
    rotary1(0, 255, 127),
    rotary2(0, 255, 127),
    rotary3(0, 255),
    rotary4(0, 255),
    scrollUp(0,1),
    scrollDown(0,1),
    slider(0, 1),
    switch1(0, 1),
    switch2(0, 1),
    switch3(0, 1),
    switch4(0, 1),
    switch5(0, 1),
    switch6(0, 1),
    toggle1(-1, 1),
    toggle2(-1, 1),
    toggle3(-1, 1),
    toggle4(-1, 1),
    miniStickForwardBackwardPivot(0, 255, 127),
    miniStickUpDownPivot(0, 255, 127) {}

const std::vector<InputLayout::Configurable>& SaitekX56Throttle::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftThrottle, "Left Throttle", "leftThrottle"));
        inputs.push_back(Configurable(rightThrottle, "Right Throttle", "rightThrottle"));
        inputs.push_back(Configurable(miniStickForwardBackwardPivot, "Forward/Backward Pivot", "miniStickForwardBackwardPivot"));
        inputs.push_back(Configurable(miniStickUpDownPivot, "Up/Down Pivot", "miniStickUpDown"));
    }
    return inputs;
}


}