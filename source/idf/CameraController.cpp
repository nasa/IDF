#include "idf/CameraController.hh"

namespace idf {

double CameraController::getPan() const {
    return active ? getCommandedPan() : 0;
}

double CameraController::getTilt() const {
    return active ? getCommandedTilt() : 0;
}

double CameraController::getSpin() const {
    return active ? getCommandedSpin() : 0;
}

double CameraController::getZoom() const {
    return active ? getCommandedZoom() : 0;
}

}
