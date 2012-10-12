#include "CompositeCameraController.hh"

using namespace hardware;

void CompositeCameraController::addCameraController(CameraController& cameraController) {
    cameraControllers.push_back(&cameraController);
}

void CompositeCameraController::removeCameraController(CameraController& cameraController) {
    for (std::vector<CameraController*>::iterator i = cameraControllers.begin();
      i != cameraControllers.end(); ++i) {
        if (*i == &cameraController) {
            cameraControllers.erase(i);
            break;
        }
    }
}

double CompositeCameraController::getPan() {
    double result = 0;
    for (std::vector<CameraController*>::iterator i = cameraControllers.begin();
      i != cameraControllers.end(); ++i) {
        result += (*i)->getPan();
    }
    return boundResult(result);
}

double CompositeCameraController::getTilt() {
    double result = 0;
    for (std::vector<CameraController*>::iterator i = cameraControllers.begin();
      i != cameraControllers.end(); ++i) {
        result += (*i)->getTilt();
    }
    return boundResult(result);
}

double CompositeCameraController::getSpin() {
    double result = 0;
    for (std::vector<CameraController*>::iterator i = cameraControllers.begin();
      i != cameraControllers.end(); ++i) {
        result += (*i)->getSpin();
    }
    return boundResult(result);
}

double CompositeCameraController::getZoom() {
    double result = 0;
    for (std::vector<CameraController*>::iterator i = cameraControllers.begin();
      i != cameraControllers.end(); ++i) {
        result += (*i)->getZoom();
    }
    return boundResult(result);
}

double CompositeCameraController::boundResult(double result) {
    return result < -1 ? -1 : result > 1 ? 1 : result;
}
