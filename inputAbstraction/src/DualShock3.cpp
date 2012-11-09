#include "DualShock3.hh"

using namespace idf;

DualShock3::DualShock3() :
    leftAnalogLeftRightPivot(0, 255, 128),
    leftAnalogUpDownPivot(0, 255, 128),
    leftAnalogIn(0, 1),
    rightAnalogLeftRightPivot(0, 255, 128),
    rightAnalogUpDownPivot(0, 255, 128),
    rightAnalogIn(0, 1),
    directionalPadUp(0, 255),
    directionalPadDown(0, 255),
    directionalPadLeft(0, 255),
    directionalPadRight(0, 255),
    selectButton(0, 1),
    playStationButton(0, 1),
    startButton(0, 1),
    squareButton(0, 255),
    triangleButton(0, 255),
    xButton(0, 255),
    circleButton(0, 255),
    leftBumper(0, 255),
    rightBumper(0, 255),
    leftTrigger(0, 255),
    rightTrigger(0, 255) {}
