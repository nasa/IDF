#include "idf/RoboticsController.hh"

namespace idf {

void RoboticsController::setActive(bool activate) {
    Controller::setActive(activate);
    inactiveRateMode = getCommandedRateMode();
}

double RoboticsController::getRoll() const {
    return active ? getCommandedRoll() : 0;
}

double RoboticsController::getPitch() const {
    return active ? getCommandedPitch() : 0;
}

double RoboticsController::getYaw() const {
    return active ? getCommandedYaw() : 0;
}

double RoboticsController::getX() const {
    return active ? getCommandedX() : 0;
}

double RoboticsController::getY() const {
    return active ? getCommandedY() : 0;
}

double RoboticsController::getZ() const {
    return active ? getCommandedZ() : 0;
}

bool RoboticsController::getTrigger() const {
    return active ? getCommandedTrigger() : false;
}

bool RoboticsController::getRateMode() const {
    return active ? getCommandedRateMode() : inactiveRateMode;
}

}
