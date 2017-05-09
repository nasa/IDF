#include "idf/CompositeFlightController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeFlightController::getCommandedRoll() const {
    return bound(accumulate(&CompositeFlightController::getRoll, std::plus<double>()));
}

double CompositeFlightController::getCommandedPitch() const {
    return bound(accumulate(&CompositeFlightController::getPitch, std::plus<double>()));
}

double CompositeFlightController::getCommandedYaw() const {
    return bound(accumulate(&CompositeFlightController::getYaw, std::plus<double>()));
}

double CompositeFlightController::getCommandedX() const {
    return bound(accumulate(&CompositeFlightController::getX, std::plus<double>()));
}

double CompositeFlightController::getCommandedY() const {
    return bound(accumulate(&CompositeFlightController::getY, std::plus<double>()));
}

double CompositeFlightController::getCommandedZ() const {
    return bound(accumulate(&CompositeFlightController::getZ, std::plus<double>()));
}

}
