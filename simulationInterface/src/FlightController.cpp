#include "FlightController.hh"

using namespace idf;

double FlightController::getRoll() const {
    return active ? getCommandedRoll() : 0;
}

double FlightController::getPitch() const {
    return active ? getCommandedPitch() : 0;
}

double FlightController::getYaw() const {
    return active ? getCommandedYaw() : 0;
}

double FlightController::getX() const {
    return active ? getCommandedX() : 0;
}

double FlightController::getY() const {
    return active ? getCommandedY() : 0;
}

double FlightController::getZ() const {
    return active ? getCommandedZ() : 0;
}
