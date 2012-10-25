#include "FlightController.hh"

using namespace idf;

double FlightController::getRoll() {
    return active ? getCommandedRoll() : 0;
}

double FlightController::getPitch() {
    return active ? getCommandedPitch() : 0;
}

double FlightController::getYaw() {
    return active ? getCommandedYaw() : 0;
}

double FlightController::getX() {
    return active ? getCommandedX() : 0;
}

double FlightController::getY() {
    return active ? getCommandedY() : 0;
}

double FlightController::getZ() {
    return active ? getCommandedZ() : 0;
}
