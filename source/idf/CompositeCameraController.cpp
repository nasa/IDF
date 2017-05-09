#include "idf/CompositeCameraController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeCameraController::getCommandedPan() const {
    return bound(accumulate(&CameraController::getPan, std::plus<double>()));
}

double CompositeCameraController::getCommandedTilt() const {
    return bound(accumulate(&CameraController::getTilt, std::plus<double>()));
}

double CompositeCameraController::getCommandedSpin() const {
    return bound(accumulate(&CameraController::getSpin, std::plus<double>()));
}

double CompositeCameraController::getCommandedZoom() const {
    return bound(accumulate(&CameraController::getZoom, std::plus<double>()));
}

}
