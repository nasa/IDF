#include "idf/SaitekX56Throttle.hh"

namespace idf {

SaitekX56Throttle::SaitekX56Throttle() :
    leftThrottle(0, 1023),
    rightThrottle(0, 1023),
    thumbForwardBackwardPivot(0, 255, 127),
    thumbUpDownPivot(0, 255, 127),
    buttonE(0, 1),
    buttonF(0, 1),
    buttonG(0, 1),
    buttonH(0, 1),
    buttonI(0, 1),
    buttonJ(0, 1),
    buttonK(0, 1),
    buttonL(0, 1),
    hat3UpDownPivot(-1,1),
    hat3ForwardBackwardPivot(-1,1),
    hat3North(0,1),
    hat3NorthEast(0,1),
    hat3East(0,1),
    hat3SouthEast(0,1),
    hat3South(0,1),
    hat3SouthWest(0,1),
    hat3West(0,1),
    hat3NorthWest(0,1),
    hat4UpDownPivot(-1,1),
    hat4ForwardBackwardPivot(-1,1),
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
    toggle4(-1, 1) {}

const std::vector<InputLayout::Configurable>& SaitekX56Throttle::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(leftThrottle, "Left Throttle", "leftThrottle"));
        inputs.push_back(Configurable(rightThrottle, "Right Throttle", "rightThrottle"));
        inputs.push_back(Configurable(thumbForwardBackwardPivot, "Forward/Backward Pivot", "thumbForwardBackwardPivot"));
        inputs.push_back(Configurable(thumbUpDownPivot, "Up/Down Pivot", "thumbUpDown"));


        /** used for testing triggers, buttons and hats
         * commented out bc not actually configurable
         */
        // inputs.push_back(Configurable(buttonE,"Button E", "buttonE"));
        // inputs.push_back(Configurable(buttonF,"Button F", "buttonF"));
        // inputs.push_back(Configurable(buttonG,"Button G", "buttonG"));
        // inputs.push_back(Configurable(buttonH,"Button H", "buttonH"));
        // inputs.push_back(Configurable(buttonI,"Button I", "buttonI"));
        // inputs.push_back(Configurable(buttonJ,"Button J", "buttonJ"));
        // inputs.push_back(Configurable(buttonK,"Button K", "buttonK"));
        // inputs.push_back(Configurable(buttonL,"Button L", "buttonL"));

        // inputs.push_back(Configurable(hat3UpDownPivot,"Hat 3 Up/Down Pivot", "hat3UpDownPivot"));
        // inputs.push_back(Configurable(hat3ForwardBackwardPivot,"Hat 3 Forward/Backward Pivot", "hat3ForwardBackwardPivot"));
        // inputs.push_back(Configurable(hat3North,"Hat 3 North", "hat3North"));
        // inputs.push_back(Configurable(hat3NorthEast,"Hat 3 North-East", "hat3NorthEast"));
        // inputs.push_back(Configurable(hat3East,"Hat 3 East", "hat3East"));
        // inputs.push_back(Configurable(hat3SouthEast,"Hat 3 South-East", "hat3SouthEast"));
        // inputs.push_back(Configurable(hat3South,"Hat 3 South", "hat3South"));
        // inputs.push_back(Configurable(hat3SouthWest,"Hat 3 South-West", "hat3SouthWest"));
        // inputs.push_back(Configurable(hat3West,"Hat 3 West", "hat3West"));
        // inputs.push_back(Configurable(hat3NorthWest,"Hat 3 North-West", "hat3NorthWest"));

        // inputs.push_back(Configurable(hat4UpDownPivot,"Hat 4 Up/Down Pivot", "hat4UpDownPivot"));
        // inputs.push_back(Configurable(hat4ForwardBackwardPivot,"Hat 4 Forward/Backward Pivot", "hat4ForwardBackwardPivot"));
        // inputs.push_back(Configurable(hat4North,"Hat 4 North", "hat4North"));
        // inputs.push_back(Configurable(hat4NorthEast,"Hat 4 North-East", "hat4NorthEast"));
        // inputs.push_back(Configurable(hat4East,"Hat 4 East", "hat4East"));
        // inputs.push_back(Configurable(hat4SouthEast,"Hat 4 South-East", "hat4SouthEast"));
        // inputs.push_back(Configurable(hat4South,"Hat 4 South", "hat4South"));
        // inputs.push_back(Configurable(hat4SouthWest,"Hat 4 South-West", "hat4SouthWest"));
        // inputs.push_back(Configurable(hat4West,"Hat 4 West", "hat4West"));
        // inputs.push_back(Configurable(hat4NorthWest,"Hat 4 North-West", "hat4NorthWest"));

        // inputs.push_back(Configurable(rotary1,"Rotary 1", "rotary1"));
        // inputs.push_back(Configurable(rotary2,"Rotary 2", "rotary2"));
        // inputs.push_back(Configurable(rotary3,"Rotary 3", "rotary3"));
        // inputs.push_back(Configurable(rotary4,"Rotary 4", "rotary4"));

        // inputs.push_back(Configurable(toggle1,"Toggle 1", "toggle1"));
        // inputs.push_back(Configurable(toggle2,"Toggle 2", "toggle2"));
        // inputs.push_back(Configurable(toggle3,"Toggle 3", "toggle3"));
        // inputs.push_back(Configurable(toggle4,"Toggle 4", "toggle4"));


        // inputs.push_back(Configurable(switch1,"Switch 1", "switch1"));
        // inputs.push_back(Configurable(switch2,"Switch 2", "switch2"));
        // inputs.push_back(Configurable(switch3,"Switch 3", "switch3"));
        // inputs.push_back(Configurable(switch4,"Switch 4", "switch4"));
        // inputs.push_back(Configurable(switch5,"Switch 5", "switch5"));
        // inputs.push_back(Configurable(switch6,"Switch 6", "switch6"));

        // inputs.push_back(Configurable(mode,"Mode", "mode"));
        // inputs.push_back(Configurable(scrollUp,"Scroll Up", "scrollUp"));
        // inputs.push_back(Configurable(scrollDown,"Scroll Down", "scrollDown"));
        // inputs.push_back(Configurable(slider,"Slider", "slider"));

    }
    return inputs;
}


}