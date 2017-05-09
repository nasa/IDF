#include "idf/CompositeRoboticsController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeRoboticsController::getCommandedRoll() const {
    return bound(accumulate(&RoboticsController::getRoll, std::plus<double>()));
}

double CompositeRoboticsController::getCommandedPitch() const {
    return bound(accumulate(&RoboticsController::getPitch, std::plus<double>()));
}

double CompositeRoboticsController::getCommandedYaw() const {
    return bound(accumulate(&RoboticsController::getYaw, std::plus<double>()));
}

double CompositeRoboticsController::getCommandedX() const {
    return bound(accumulate(&RoboticsController::getX, std::plus<double>()));
}

double CompositeRoboticsController::getCommandedY() const {
    return bound(accumulate(&RoboticsController::getY, std::plus<double>()));
}

double CompositeRoboticsController::getCommandedZ() const {
    return bound(accumulate(&CompositeRoboticsController::getZ, std::plus<double>()));
}

bool CompositeRoboticsController::getCommandedTrigger() const {
    return accumulate(&CompositeRoboticsController::getTrigger, std::logical_or<bool>());
}

bool CompositeRoboticsController::getCommandedRateMode() const {
    return accumulate(&CompositeRoboticsController::getRateMode, std::logical_or<bool>());
}

}
