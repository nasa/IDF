#include "CompositeFlightController.hh"
#include "inputAbstraction/include/Utils.hh"
#include <algorithm>

using namespace idf;

void CompositeFlightController::add(FlightController& flightController) {
    // Add the controller, if not present.
    if (std::find(flightControllers.begin(), flightControllers.end(), &flightController) == flightControllers.end()) {
        flightControllers.push_back(&flightController);
    }
}

void CompositeFlightController::remove(const FlightController& flightController) {
    // Remove the controller, if present.
    flightControllers.erase(std::remove(flightControllers.begin(),
      flightControllers.end(), &flightController), flightControllers.end());
}

double CompositeFlightController::getCommandedRoll() const {
    double result = 0;

    // Sum all constituent controller's roll commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getRoll();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedPitch() const {
    double result = 0;

    // Sum all constituent controller's pitch commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getPitch();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedYaw() const {
    double result = 0;

    // Sum all constituent controller's yaw commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getYaw();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedX() const {
    double result = 0;

    // Sum all constituent controller's x commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getX();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedY() const {
    double result = 0;

    // Sum all constituent controller's y commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getY();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeFlightController::getCommandedZ() const {
    double result = 0;

    // Sum all constituent controller's z commands.
    for (std::vector<FlightController*>::const_iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getZ();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

void CompositeFlightController::setActive(bool activate) {
    // Set all constituent controller's states.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        (*i)->setActive(activate);
    }

    // Call the parent method to set this instance's state.
    Controller::setActive(activate);
}
