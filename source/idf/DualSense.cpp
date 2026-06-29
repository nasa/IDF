#include "idf/DualSense.hh"
#include <iostream>

namespace idf {

DualSense::DualSense() :
    leftTriggerDiscrete(0,1),
    rightTriggerDiscrete(0,1),
    mute(0,1),
    anglularVelocityX(-1,1),
    anglularVelocityY(-1,1),
    anglularVelocityZ(-1,1),
    accelerationX(-1,1),
    accelerationY(-1,1),
    accelerationZ(-1,1) {

    for (unsigned i = 0; i < sizeof(command); ++i) {
        command[i] = 0;
    }
    command[0] = 0x11; // bluetooth report ID
    command[1] = 0x80; // ?
    command[2] = 0x05; // USB report ID
    command[3] = 0xFF; // enable motors

    trackpad.finger1.y.configure(0, 0x437);
    trackpad.finger2.y.configure(0, 0x437);
}

void DualSense::rumble(Rumbler rumbler, unsigned char intensity) {
    command[rumbler == Weak ? 6 : 7] = intensity;
    sendCommand();
}

void DualSense::setLightBarColor(unsigned char red, unsigned char green, unsigned char blue) {
    command[8] = red;
    command[9] = green;
    command[10] = blue;
    sendCommand();
}

void DualSense::setLightBarCycle(unsigned char on, unsigned char off) {
    command[11] = on;
    command[12] = off;
    sendCommand();
}

const std::vector<InputLayout::Configurable>& DualSense::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(DualShock::getConfigurables(), inputs);
        inputs.push_back(Configurable(directionalPadUp, "Directional Pad Up", "directionalPadUp"));
        inputs.push_back(Configurable(directionalPadDown, "Directional Pad Down", "directionalPadDown"));
        inputs.push_back(Configurable(directionalPadLeft, "Directional Pad Left", "directionalPadLeft"));
        inputs.push_back(Configurable(directionalPadRight, "Directional Pad Right", "directionalPadRight"));
        inputs.push_back(Configurable(squareButton, "Square Button", "squareButton"));
        inputs.push_back(Configurable(triangleButton, "Triangle Button", "triangleButton"));
        inputs.push_back(Configurable(xButton, "X Button", "xButton"));
        inputs.push_back(Configurable(circleButton, "Circle Button", "circleButton"));
        inputs.push_back(Configurable(leftBumper, "Left Bumper", "leftBumper"));
        inputs.push_back(Configurable(rightBumper, "Right Bumper", "rightBumper"));
        inputs.push_back(Configurable(anglularVelocityX, "Angular Vel X", "angulatVelocityX"));
        inputs.push_back(Configurable(anglularVelocityY, "Angular Vel Y", "angulatVelocityY"));
        inputs.push_back(Configurable(anglularVelocityZ, "Angular Vel Z", "angulatVelocityZ"));
        inputs.push_back(Configurable(accelerationX, "Accel X", "accelerationX"));
        inputs.push_back(Configurable(accelerationY, "Accel Y", "accelerationY"));
        inputs.push_back(Configurable(accelerationZ, "Accel Z", "accelerationZ"));
    }
    return inputs;
}

} // namespace idf
