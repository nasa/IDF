#include "idf/CompositeCameraController.hh"
#include "idf/Utils.hh"
#include <algorithm>

namespace idf {

double CompositeCameraController::getCommandedPan() const {
    double result = 0;

    // Sum all constituent controller's pan commands.
    for (std::vector<CameraController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getPan();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeCameraController::getCommandedTilt() const {
    double result = 0;

    // Sum all constituent controller's tilt commands.
    for (std::vector<CameraController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getTilt();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeCameraController::getCommandedSpin() const {
    double result = 0;

    // Sum all constituent controller's spin commands.
    for (std::vector<CameraController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getSpin();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

double CompositeCameraController::getCommandedZoom() const {
    double result = 0;

    // Sum all constituent controller's zoom commands.
    for (std::vector<CameraController*>::const_iterator i = components.begin();
      i != components.end(); ++i) {
        result += (*i)->getZoom();
    }

    // Restrict the result to [-1, 1]
    return bound(result);
}

}
