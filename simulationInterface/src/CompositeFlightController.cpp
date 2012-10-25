#include "CompositeFlightController.hh"

#include <algorithm>

using namespace idf;

void CompositeFlightController::add(FlightController& flightController) {
    // Add the controller, if not present.
    if(std::find(flightControllers.begin(), flightControllers.end(), &flightController) == flightControllers.end()) {
        flightControllers.push_back(&flightController);
    }
}

void CompositeFlightController::remove(FlightController& flightController) {
    // Remove the controller, if present.
    flightControllers.erase(std::remove(flightControllers.begin(),
      flightControllers.end(), &flightController), flightControllers.end());
}

double CompositeFlightController::getCommandedRoll() {
    double result = 0;

    // Sum all consituent controller's roll commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getRoll();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

double CompositeFlightController::getCommandedPitch() {
    double result = 0;

    // Sum all consituent controller's pitch commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getPitch();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

double CompositeFlightController::getCommandedYaw() {
    double result = 0;

    // Sum all consituent controller's yaw commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getYaw();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

double CompositeFlightController::getCommandedX() {
    double result = 0;

    // Sum all consituent controller's x commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getX();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

double CompositeFlightController::getCommandedY() {
    double result = 0;

    // Sum all consituent controller's y commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getY();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

double CompositeFlightController::getCommandedZ() {
    double result = 0;

    // Sum all consituent controller's z commands.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getZ();
    }

    // Restrict the result to [-1, 1]
    return result > 1 ? 1 : result < -1 ? -1 : result;
}

void CompositeFlightController::setActive(bool active) {
    // Set all consituent controller's states.
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        (*i)->setActive(active);
    }

    // Call the parent method to set this instance's state.
    Controller::setActive(active);
}
