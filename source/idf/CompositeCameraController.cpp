#include "idf/CompositeCameraController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeCameraController::getCommandedPan() const {
    return bound(accumulate(&CompositeCameraController::getPan, std::plus<double>()));
}

double CompositeCameraController::getCommandedTilt() const {
    return bound(accumulate(&CompositeCameraController::getTilt, std::plus<double>()));
}

double CompositeCameraController::getCommandedSpin() const {
    return bound(accumulate(&CompositeCameraController::getSpin, std::plus<double>()));
}

double CompositeCameraController::getCommandedZoom() const {
    return bound(accumulate(&CompositeCameraController::getZoom, std::plus<double>()));
}

}
