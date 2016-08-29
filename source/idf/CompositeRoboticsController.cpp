#include "idf/CompositeRoboticsController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeRoboticsController::getCommandedRoll() const {
    double result = 0;

    // Sum all constituent controller's roll commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getRoll();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeRoboticsController::getCommandedPitch() const {
    double result = 0;

    // Sum all constituent controller's pitch commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getPitch();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeRoboticsController::getCommandedYaw() const {
    double result = 0;

    // Sum all constituent controller's yaw commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getYaw();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeRoboticsController::getCommandedX() const {
    double result = 0;

    // Sum all constituent controller's x commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getX();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeRoboticsController::getCommandedY() const {
    double result = 0;

    // Sum all constituent controller's y commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getY();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeRoboticsController::getCommandedZ() const {
    double result = 0;

    // Sum all constituent controller's z commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getZ();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

bool CompositeRoboticsController::getCommandedTrigger() const {
    bool result = false;

    // Perform a logical OR on all constituent controller's trigger commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result = result || (*i)->getTrigger();
    }

    return result;
}

bool CompositeRoboticsController::getCommandedRateMode() const {
    bool result = false;

    // Perform a logical OR on all constituent controller's rate mode commands.
    for (std::vector<RoboticsController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result = result || (*i)->getRateMode();
    }

    return result;
}

}
