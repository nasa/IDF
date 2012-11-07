#include "XBox.hh"

using namespace idf;

XBox::XBox() :
    leftAnalogLeftRightPivot(0x80, 0xFF7F),
    leftAnalogUpDownPivot(0x80, 0xFF7F),
    leftAnalogIn(0, 1),
    rightAnalogLeftRightPivot(0x80, 0xFF7F),
    rightAnalogUpDownPivot(0x80, 0xFF7F),
    rightAnalogIn(0, 1),
    directionalPadUp(0, 1),
    directionalPadDown(0, 1),
    directionalPadLeft(0, 1),
    directionalPadRight(0, 1),
    backButton(0, 1),
    xBoxButton(0, 1),
    startButton(0, 1),
    xButton(0, 1),
    yButton(0, 1),
    aButton(0, 1),
    bButton(0, 1),
    leftBumper(0, 1),
    rightBumper(0, 1),
    leftTrigger(0, 1),
    rightTrigger(0, 1) {}
