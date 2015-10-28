#include "inputAbstraction/include/DualShock4.hh"

using namespace idf;

DualShock4::DualShock4() :
    shareButton(0, 1),
    optionsButton(0, 1) {

    for (unsigned i = 0; i < sizeof(command); ++i) {
        command[i] = 0;
    }
    command[0] = 0x11; // bluetooth report ID
    command[1] = 0x80; // ?
    command[2] = 0x05; // USB report ID
    command[3] = 0xFF; // enable motors
}

DualShock4::Trackpad::Trackpad() :
    button(0, 1) {}

DualShock4::Trackpad::Finger::Finger() :
    contact(0, 1),
    x(0, 0x77F),
    y(0, 0x3AD) {}

void DualShock4::rumble(Rumbler rumbler, unsigned char intensity) {
    command[rumbler == Weak ? 6 : 7] = intensity;
    sendCommand();
}

void DualShock4::setLightBarColor(unsigned char red, unsigned char green, unsigned char blue) {
    command[8] = red;
    command[9] = green;
    command[10] = blue;
    sendCommand();
}

void DualShock4::setLightBarCycle(unsigned char on, unsigned char off) {
    command[11] = on;
    command[12] = off;
    sendCommand();
}
