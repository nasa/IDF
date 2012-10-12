#include "SingleCameraController.hh"
#include "inputAbstraction/include/CompositeInput.hh"

using namespace hardware;

SingleCameraController::SingleCameraController(Input& pan, Input& tilt, Input& Spin, Input& zoom) :
    mPan(&pan), mTilt(&tilt), mSpin(&Spin), mZoom(&zoom) {}

double SingleCameraController::getPan() {
    return mPan->getValue();
}

double SingleCameraController::getTilt() {
    return mTilt->getValue();
}

double SingleCameraController::getSpin() {
    return mSpin->getValue();
}

double SingleCameraController::getZoom() {
    return mZoom->getValue();
}

Input& SingleCameraController::getPanInput() {
    return *mPan;
}

Input& SingleCameraController::getTiltInput() {
    return *mTilt;
}

Input& SingleCameraController::getSpinInput() {
    return *mSpin;
}

Input& SingleCameraController::getZoomInput() {
    return *mZoom;
}

void SingleCameraController::setPan(Input& pan) {
    mPan = &pan;
}

void SingleCameraController::setTilt(Input& tilt) {
    mTilt = &tilt;
}

void SingleCameraController::setSpin(Input& Spin) {
    mSpin = &Spin;
}

void SingleCameraController::setZoom(Input& zoom) {
    mZoom = &zoom;
}
