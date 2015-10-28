#include "simulationInterface/include/CompositeFlightController.hh"
#include "inputAbstraction/include/Utils.hh"
#include <algorithm>

using namespace idf;

double CompositeFlightController::getCommandedRoll() const {
    double result = 0;

    // Sum all constituent controller's roll commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getRoll();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedPitch() const {
    double result = 0;

    // Sum all constituent controller's pitch commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getPitch();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedYaw() const {
    double result = 0;

    // Sum all constituent controller's yaw commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getYaw();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedX() const {
    double result = 0;

    // Sum all constituent controller's x commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getX();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedY() const {
    double result = 0;

    // Sum all constituent controller's y commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getY();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedZ() const {
    double result = 0;

    // Sum all constituent controller's z commands.
    for (std::vector<FlightController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getZ();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}
