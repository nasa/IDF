#include "idf/SaitekX56Stick.hh"

namespace idf {

SaitekX56Stick::SaitekX56Stick() :
    forwardBackwardPivot(0, 65535, 32767),
    leftRightPivot(0, 65535, 32767),
    twist(0, 4095, 2047),
    thumbForwardBackwardPivot(0, 255, 127),
    thumbLeftRightPivot(0, 255, 127),
    trigger1(0, 1),
    trigger2(0, 1),
    buttonA(0, 1),
    buttonB(0, 1),
    buttonC(0, 1),
    buttonD(0, 1),
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
    povUpDownPivot(-1,1),
    povLeftRightPivot(-1,1),
    povNorth(0,1),
    povNorthEast(0,1),
    povEast(0,1),
    povSouthEast(0,1),
    povSouth(0,1),
    povSouthWest(0,1),
    povWest(0,1),
    povNorthWest(0,1) {}

const std::vector<InputLayout::Configurable>& SaitekX56Stick::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
        inputs.push_back(Configurable(twist, "Twist", "twist"));
        inputs.push_back(Configurable(thumbForwardBackwardPivot, "Thumb Forward/Backward Pivot", "thumbForwardBackwardPivot"));
        inputs.push_back(Configurable(thumbLeftRightPivot, "Thumb Left/Right Pivot", "thumbLeftRightPivot"));

        /** used for testing triggers, buttons and hats
         * commented out bc not actually configurable
         */
        // inputs.push_back(Configurable(trigger1,"Trigger 1", "trigger1"));
        // inputs.push_back(Configurable(trigger2,"Trigger 2", "trigger2"));
        // inputs.push_back(Configurable(buttonA,"Button A", "buttonA"));
        // inputs.push_back(Configurable(buttonB,"Button B", "buttonB"));
        // inputs.push_back(Configurable(buttonC,"Button C", "buttonC"));
        // inputs.push_back(Configurable(buttonD,"Button D", "buttonD"));

        // inputs.push_back(Configurable(hat1UpDownPivot,"Hat 1 Up/Down Pivot", "hat1UpDownPivot"));
        // inputs.push_back(Configurable(hat1LeftRightPivot,"Hat 1 Left/Right Pivot", "hat1LeftRightPivot"));
        // inputs.push_back(Configurable(hat1North,"Hat 1 North", "hat1North"));
        // inputs.push_back(Configurable(hat1NorthEast,"Hat 1 North-East", "hat1NorthEast"));
        // inputs.push_back(Configurable(hat1East,"Hat 1 East", "hat1East"));
        // inputs.push_back(Configurable(hat1SouthEast,"Hat 1 South-East", "hat1SouthEast"));
        // inputs.push_back(Configurable(hat1South,"Hat 1 South", "hat1South"));
        // inputs.push_back(Configurable(hat1SouthWest,"Hat 1 South-West", "hat1SouthWest"));
        // inputs.push_back(Configurable(hat1West,"Hat 1 West", "hat1West"));
        // inputs.push_back(Configurable(hat1NorthWest,"Hat 1 North-West", "hat1NorthWest"));

        // inputs.push_back(Configurable(hat2UpDownPivot,"Hat 2 Up/Down Pivot", "hat2UpDownPivot"));
        // inputs.push_back(Configurable(hat2LeftRightPivot,"Hat 2 Left/Right Pivot", "hat2LeftRightPivot"));
        // inputs.push_back(Configurable(hat2North,"Hat 2 North", "hat2North"));
        // inputs.push_back(Configurable(hat2NorthEast,"Hat 2 North-East", "hat2NorthEast"));
        // inputs.push_back(Configurable(hat2East,"Hat 2 East", "hat2East"));
        // inputs.push_back(Configurable(hat2SouthEast,"Hat 2 South-East", "hat2SouthEast"));
        // inputs.push_back(Configurable(hat2South,"Hat 2 South", "hat2South"));
        // inputs.push_back(Configurable(hat2SouthWest,"Hat 2 South-West", "hat2SouthWest"));
        // inputs.push_back(Configurable(hat2West,"Hat 2 West", "hat2West"));
        // inputs.push_back(Configurable(hat2NorthWest,"Hat 2 North-West", "hat2NorthWest"));

        // inputs.push_back(Configurable(povUpDownPivot,"POV Up/Down Pivot", "povUpDownPivot"));
        // inputs.push_back(Configurable(povLeftRightPivot,"POV Left/Right Pivot", "povLeftRightPivot"));
        // inputs.push_back(Configurable(povNorth,"POV North", "povNorth"));
        // inputs.push_back(Configurable(povNorthEast,"POV North-East", "povNorthEast"));
        // inputs.push_back(Configurable(povEast,"POV East", "povEast"));
        // inputs.push_back(Configurable(povSouthEast,"POV South-East", "povSouthEast"));
        // inputs.push_back(Configurable(povSouth,"POV South", "povSouth"));
        // inputs.push_back(Configurable(povSouthWest,"POV South-West", "povSouthWest"));
        // inputs.push_back(Configurable(povWest,"POV West", "povWest"));
        // inputs.push_back(Configurable(povNorthWest,"POV North-West", "povNorthWest"));
    }
    return inputs;
}


}