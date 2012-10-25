#include "CameraController.hh"

using namespace idf;

double CameraController::getPan() {
    return active ? getCommandedPan() : 0;
}

double CameraController::getTilt() {
    return active ? getCommandedTilt() : 0;
}

double CameraController::getSpin() {
    return active ? getCommandedSpin() : 0;
}

double CameraController::getZoom() {
    return active ? getCommandedZoom() : 0;
}
