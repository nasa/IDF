#include "CompositeFlightController.hh"

using namespace hardware;

void CompositeFlightController::addFlightController(FlightController& flightController) {
    flightControllers.push_back(&flightController);
}

void CompositeFlightController::removeFlightController(FlightController& flightController) {
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        if (*i == &flightController) {
            flightControllers.erase(i);
            break;
        }
    }
}

double CompositeFlightController::getRoll() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getRoll();
    }
    return boundResult(result);
}

double CompositeFlightController::getPitch() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getPitch();
    }
    return boundResult(result);
}

double CompositeFlightController::getYaw() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getYaw();
    }
    return boundResult(result);
}

double CompositeFlightController::getX() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getX();
    }
    return boundResult(result);
}

double CompositeFlightController::getY() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getY();
    }
    return boundResult(result);
}

double CompositeFlightController::getZ() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getZ();
    }
    return boundResult(result);
}

double CompositeFlightController::boundResult(double result) {
    return result < -1 ? -1 : result > 1 ? 1 : result;
}
