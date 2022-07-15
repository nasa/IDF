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
    hat1UpDownPivot(-1,1),
    hat1LeftRightPivot(-1,1),
    hat1North(0,1),
    hat1NorthEast(0,1),
    hat1East(0,1),
    hat1SouthEast(0,1),
    hat1South(0,1),
    hat1SouthWest(0,1),
    hat1West(0,1),
    hat1NorthWest(0,1),
    hat2UpDownPivot(-1,1),
    hat2LeftRightPivot(-1,1),
    hat2North(0,1),
    hat2NorthEast(0,1),
    hat2East(0,1),
    hat2SouthEast(0,1),
    hat2South(0,1),
    hat2SouthWest(0,1),
    hat2West(0,1),
    hat2NorthWest(0,1),
    hat3UpDownPivot(-1,1),
    hat3LeftRightPivot(-1,1),
    hat3North(0,1),
    hat3NorthEast(0,1),
    hat3East(0,1),
    hat3SouthEast(0,1),
    hat3South(0,1),
    hat3SouthWest(0,1),
    hat3West(0,1),
    hat3NorthWest(0,1),
    mode(1,3),
    mode1(0,1),
    mode2(0,1),
    mode3(0,1),
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

        // inputs.push_back(Configurable(trigger, "Trigger", "trigger"));
        // inputs.push_back(Configurable(triggerStage2, "Triger Stage 2", "triggerStage2"));
        // inputs.push_back(Configurable(trigger2, "Pinky Trigger", "trigger2"));
        // inputs.push_back(Configurable(buttonFire, "Fire Button", "buttonFire"));
        // inputs.push_back(Configurable(buttonA, "A Button", "buttonA"));
        // inputs.push_back(Configurable(buttonB, "B Button", "buttonB"));
        // inputs.push_back(Configurable(buttonC, "C Button", "buttonC"));
        inputs.push_back(Configurable(mode, "Mode switch", "mode"));
        inputs.push_back(Configurable(mode1, "Mode 1", "mode1"));
        inputs.push_back(Configurable(mode2, "Mode 2", "mode2"));
        inputs.push_back(Configurable(mode3, "Mode 3", "mode3"));
        // inputs.push_back(Configurable(toggle1, "Toggle 1", "toggle1"));
        // inputs.push_back(Configurable(toggle2, "Toggle 2", "toggle2"));
        // inputs.push_back(Configurable(toggle3, "Toggle 3", "toggle3"));
        // inputs.push_back(Configurable(toggle4, "Toggle 4", "toggle4"));
        // inputs.push_back(Configurable(toggle5, "Toggle 5", "toggle5"));
        // inputs.push_back(Configurable(toggle6, "Toggle 6", "toggle6"));
        inputs.push_back(Configurable(hat1UpDownPivot, "Hat 1 Up/Down Pivot", "hat1UpDownPivot"));
        inputs.push_back(Configurable(hat1LeftRightPivot, "Hat 1 Left/Right Pivot", "hat1LeftRightPivot"));
        // inputs.push_back(Configurable(hat1North, "Hat 1 North", "hat1North"));
        // inputs.push_back(Configurable(hat1NorthEast, "Hat 1 NorthEast", "hat1NorthEast"));
        // inputs.push_back(Configurable(hat1East, "Hat 1 East", "hat1East"));
        // inputs.push_back(Configurable(hat1SouthEast, "Hat 1 SouthEast", "hat1SouthEast"));
        // inputs.push_back(Configurable(hat1South, "Hat 1 South", "hat1South"));
        // inputs.push_back(Configurable(hat1SouthWest, "Hat 1 SouthWest", "hat1SouthWest"));
        // inputs.push_back(Configurable(hat1West, "Hat 1 West", "hat1West"));
        // inputs.push_back(Configurable(hat1NorthWest, "Hat 1 NorthWest", "hat1NorthWest"));
        inputs.push_back(Configurable(hat2UpDownPivot, "Hat 2 Up/Down Pivot", "hat2UpDownPivot"));
        inputs.push_back(Configurable(hat2LeftRightPivot, "Hat 2 Left/Right Pivot", "hat2LeftRightPivot"));
        // inputs.push_back(Configurable(hat2North, "Hat 2 North", "hat2North"));
        // inputs.push_back(Configurable(hat2NorthEast, "Hat 2 NorthEast", "hat2NorthEast"));
        // inputs.push_back(Configurable(hat2East, "Hat 2 East", "hat2East"));
        // inputs.push_back(Configurable(hat2SouthEast, "Hat 2 SouthEast", "hat2SouthEast"));
        // inputs.push_back(Configurable(hat2South, "Hat 2 South", "hat2South"));
        // inputs.push_back(Configurable(hat2SouthWest, "Hat 2 SouthWest", "hat2SouthWest"));
        // inputs.push_back(Configurable(hat2West, "Hat 2 West", "hat2West"));
        // inputs.push_back(Configurable(hat2NorthWest, "Hat 2 NorthWest", "hat2NorthWest"));

        // inputs.push_back(Configurable(buttonD, "D Button", "buttonD"));
        // inputs.push_back(Configurable(buttonE, "E Button", "buttonE"));
        // inputs.push_back(Configurable(buttonI, "i Button", "buttonI"));
        // inputs.push_back(Configurable(mouseLeftClick, "Mouse Left Click", "mouseLeftClick"));
        inputs.push_back(Configurable(hat3UpDownPivot, "Hat 3 Up/Down Pivot", "hat3UpDownPivot"));
        inputs.push_back(Configurable(hat3LeftRightPivot, "Hat 3 Left/Right Pivot", "hat3LeftRightPivot"));
        // inputs.push_back(Configurable(hat3North, "Hat 3 North", "hat3North"));
        // inputs.push_back(Configurable(hat3NorthEast, "Hat 3 NorthEast", "hat3NorthEast"));
        // inputs.push_back(Configurable(hat3East, "Hat 3 East", "hat3East"));
        // inputs.push_back(Configurable(hat3SouthEast, "Hat 3 SouthEast", "hat3SouthEast"));
        // inputs.push_back(Configurable(hat3South, "Hat 3 South", "hat3South"));
        // inputs.push_back(Configurable(hat3SouthWest, "Hat 3 SouthWest", "hat3SouthWest"));
        // inputs.push_back(Configurable(hat3West, "Hat 3 West", "hat3West"));
        // inputs.push_back(Configurable(hat3NorthWest, "Hat 3 NorthWest", "hat3NorthWest"));
        // inputs.push_back(Configurable(buttonFunction, "MFD Function Button", "buttonFunction"));
        // inputs.push_back(Configurable(buttonStartStop, "MDF Start/Stop Button", "buttonStartStop"));
        // inputs.push_back(Configurable(buttonReset, "MFD Reset Button", "buttonReset"));
        // inputs.push_back(Configurable(rotary1, "Rotary 1", "rotary1"));
        // inputs.push_back(Configurable(rotary2, "Rotary 2", "rotary2"));
        // inputs.push_back(Configurable(scrollUp, "Scroll Up", "scrollUp"));
        // inputs.push_back(Configurable(scrollDown, "Scroll Down", "scrollDown"));

    return inputs;
}

}
