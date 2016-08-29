/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CompositeCameraController.cpp)
(idf/Utils.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CompositeCameraController.cpp}
 * @trick_link_dependency{idf/Utils.cpp}
 */

#ifndef COMPOSITE_CAMERA_CONTROLLER_HH
#define COMPOSITE_CAMERA_CONTROLLER_HH

#include "idf/CompositeController.hh"
#include "idf/CameraController.hh"

namespace idf {

#ifdef SWIG
%template(CompositeControllerCameraController) CompositeController<CameraController>;
#endif

/**
 * combines multiple {@link CameraController}s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeCameraController : public CompositeController<CameraController> {

    public:

    /**
     * gets the conglomerate pan value, normalized to [-1, 0, 1]
     *
     * @return the combined pan of all added camera controllers
     */
    double getCommandedPan() const;

    /**
     * gets the conglomerate tilt value, normalized to [-1, 0, 1]
     *
     * @return the combined tilt of all added camera controllers
     */
    double getCommandedTilt() const;

    /**
     * gets the conglomerate spin value, normalized to [-1, 0, 1]
     *
     * @return the combined spin of all added camera controllers
     */
    double getCommandedSpin() const;

    /**
     * gets the conglomerate zoom value, normalized to [-1, 0, 1]
     *
     * @return the combined zoom of all added camera controllers
     */
    double getCommandedZoom() const;

};

}

#endif
