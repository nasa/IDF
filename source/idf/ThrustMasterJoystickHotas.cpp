#include "idf/ThrustMasterJoystickHotas.hh"

namespace idf {

ThrustMasterJoystickHotas::ThrustMasterJoystickHotas() : 
    forwardBackwardPivot(0, 65535, 32767),
    leftRightPivot(0, 65535, 32767),
    trigger(0, 1),
    triggerStage2(0, 1),
    button2(0, 1),
    button3(0, 1),
    button4(0, 1),
    button5(0, 1),
    button19(0, 1),
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
    hat4UpDownPivot(-1,1),
    hat4LeftRightPivot(-1,1),
    hat4North(0,1),
    hat4East(0,1),
    hat4South(0,1),
    hat4West(0,1)
    {}

const std::vector<InputLayout::Configurable>& ThrustMasterJoystickHotas::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left Right Pivot", "leftRightPivot"));

        // inputs.push_back(Configurable(trigger, "Trigger", "trigger"));
        // inputs.push_back(Configurable(triggerStage2, "Triger Stage 2", "triggerStage2"));
        // inputs.push_back(Configurable(trigger2, "Pinky Trigger", "trigger2"));
        // inputs.push_back(Configurable(button2, "2 Button", "button2"));
        // inputs.push_back(Configurable(button3, "3 Button", "button3"));
        // inputs.push_back(Configurable(button4, "4 Button", "button4"));
        // inputs.push_back(Configurable(button5, "5 Button", "button5"));
        // inputs.push_back(Configurable(button19, "19 Button", "button19"));

        // inputs.push_back(Configurable(hat1UpDownPivot, "Hat 1 Up/Down Pivot", "hat1UpDownPivot"));
        // inputs.push_back(Configurable(hat1LeftRightPivot, "Hat 1 Left/Right Pivot", "hat1LeftRightPivot"));
        // inputs.push_back(Configurable(hat1North, "Hat 1 North", "hat1North"));
        // inputs.push_back(Configurable(hat1NorthEast, "Hat 1 NorthEast", "hat1NorthEast"));
        // inputs.push_back(Configurable(hat1East, "Hat 1 East", "hat1East"));
        // inputs.push_back(Configurable(hat1SouthEast, "Hat 1 SouthEast", "hat1SouthEast"));
        // inputs.push_back(Configurable(hat1South, "Hat 1 South", "hat1South"));
        // inputs.push_back(Configurable(hat1SouthWest, "Hat 1 SouthWest", "hat1SouthWest"));
        // inputs.push_back(Configurable(hat1West, "Hat 1 West", "hat1West"));
        // inputs.push_back(Configurable(hat1NorthWest, "Hat 1 NorthWest", "hat1NorthWest"));

        // inputs.push_back(Configurable(hat2UpDownPivot, "Hat 2 Up/Down Pivot", "hat2UpDownPivot"));
        // inputs.push_back(Configurable(hat2LeftRightPivot, "Hat 2 Left/Right Pivot", "hat2LeftRightPivot"));
        // inputs.push_back(Configurable(hat2North, "Hat 2 North", "hat2North"));
        // inputs.push_back(Configurable(hat2NorthEast, "Hat 2 NorthEast", "hat2NorthEast"));
        // inputs.push_back(Configurable(hat2East, "Hat 2 East", "hat2East"));
        // inputs.push_back(Configurable(hat2SouthEast, "Hat 2 SouthEast", "hat2SouthEast"));
        // inputs.push_back(Configurable(hat2South, "Hat 2 South", "hat2South"));
        // inputs.push_back(Configurable(hat2SouthWest, "Hat 2 SouthWest", "hat2SouthWest"));
        // inputs.push_back(Configurable(hat2West, "Hat 2 West", "hat2West"));
        // inputs.push_back(Configurable(hat2NorthWest, "Hat 2 NorthWest", "hat2NorthWest"));

        // inputs.push_back(Configurable(hat3UpDownPivot, "Hat 3 Up/Down Pivot", "hat3UpDownPivot"));
        // inputs.push_back(Configurable(hat3LeftRightPivot, "Hat 3 Left/Right Pivot", "hat3LeftRightPivot"));
        // inputs.push_back(Configurable(hat3North, "Hat 3 North", "hat3North"));
        // inputs.push_back(Configurable(hat3NorthEast, "Hat 3 NorthEast", "hat3NorthEast"));
        // inputs.push_back(Configurable(hat3East, "Hat 3 East", "hat3East"));
        // inputs.push_back(Configurable(hat3SouthEast, "Hat 3 SouthEast", "hat3SouthEast"));
        // inputs.push_back(Configurable(hat3South, "Hat 3 South", "hat3South"));
        // inputs.push_back(Configurable(hat3SouthWest, "Hat 3 SouthWest", "hat3SouthWest"));
        // inputs.push_back(Configurable(hat3West, "Hat 3 West", "hat3West"));
        // inputs.push_back(Configurable(hat3NorthWest, "Hat 3 NorthWest", "hat3NorthWest"));

        // inputs.push_back(Configurable(hat4UpDownPivot, "Hat 4 Up/Down Pivot", "hat4UpDownPivot"));
        // inputs.push_back(Configurable(hat4LeftRightPivot, "Hat 4 Left/Right Pivot", "hat4LeftRightPivot"));
        // inputs.push_back(Configurable(hat4North, "Hat 4 North", "hat4North"));
        // inputs.push_back(Configurable(hat4East, "Hat 4 East", "hat4East"));
        // inputs.push_back(Configurable(hat4South, "Hat 4 South", "hat4South"));
        // inputs.push_back(Configurable(hat4West, "Hat 4 West", "hat4West"));
    }

    return inputs;
}

}
