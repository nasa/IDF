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
    rightTrigger(0, 255) {
    command[0] = 1;
    command[1] = 0;
    command[2] = 0;
    command[3] = 0;
    command[4] = 0;
    command[5] = 0;
    command[6] = 0;
    command[7] = 0;
    command[8] = 0;
    command[9] = 0x1E;
    command[10] = 0;
    command[11] = 0;
    command[12] = 0;
    command[13] = 0;
    command[14] = 0;
    command[15] = 0;
    command[16] = 0;
    command[17] = 0;
    command[18] = 0;
    command[19] = 0;
    command[20] = 0;
    command[21] = 0;
    command[22] = 0;
    command[23] = 0;
    command[24] = 0;
    command[25] = 0;
    command[26] = 0;
    command[27] = 0;
    command[28] = 0;
    command[29] = 0;
}

void DualShock3::setRumbleCommand(Rumbler rumbler, unsigned char duration, unsigned char intensity) {
    int index = rumbler == HighFrequency ? 1 : 3;
    command[index] = duration;
    command[++index] = intensity;
}

void DualShock3::setLedCommand(LED led, unsigned char commandDuration,
  unsigned char cyclePeriodInteger, unsigned char cyclePeriodFraction,
  unsigned char offFactor, unsigned char onFactor) {
    int index = 10 + 5 * led;
    command[index] = commandDuration;
    command[++index] = cyclePeriodInteger;
    command[++index] = cyclePeriodFraction;
    command[++index] = offFactor;
    command[++index] = onFactor;
}
