#include "idf/FlightController.hh"

namespace idf {

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

bool  FlightController::getTrigger() const {
    return active ? getCommandedTrigger() : false;
}

bool  FlightController::getComm() const {
    return active ? getCommandedComm() : false;
}

bool  FlightController::getShutdown() const {
    return active ? getCommandedShutdown() : false;
}

}
