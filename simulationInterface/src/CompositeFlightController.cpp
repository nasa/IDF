#include "CompositeFlightController.hh"

using namespace idf;

void CompositeFlightController::add(FlightController& flightController) {
    flightControllers.push_back(&flightController);
}

void CompositeFlightController::remove(FlightController& flightController) {
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
    return result;
}

double CompositeFlightController::getPitch() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getPitch();
    }
    return result;
}

double CompositeFlightController::getYaw() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getYaw();
    }
    return result;
}

double CompositeFlightController::getX() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getX();
    }
    return result;
}

double CompositeFlightController::getY() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getY();
    }
    return result;
}

double CompositeFlightController::getZ() {
    double result = 0;
    for (std::vector<FlightController*>::iterator i = flightControllers.begin();
      i != flightControllers.end(); ++i) {
        result += (*i)->getZ();
    }
    return result;
}
