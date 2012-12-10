/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeCameraController.cpp))
 */

#ifndef _COMPOSITE_CAMERA_CONTROLLER_HH_
#define _COMPOSITE_CAMERA_CONTROLLER_HH_

#include "CameraController.hh"
#include <vector>

namespace idf {

/**
 * combines multiple <code>CameraController</code>s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeCameraController : public CameraController {

    public:

    /**
     * adds <code>cameraController</code>, combining its values with all other
     * added <code>CameraController</code>s. Adding a controller that is
     * already contained by this instance has no effect.
     */
    void add(CameraController& cameraController);

    /**
     * removes <code>cameraController</code>, no longer combining its values
     * with other <code>CameraController</code>s. Removing a controller
     * that is not contained by this instance has no effect.
     */
    void remove(const CameraController& cameraController);

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

    /**
     * sets the active state of this controller and all consituent controllers
     * and notifies all registered listeners of any change. Inactive controllers
     * output neutral or default values when polled.
     *
     * @param active the state to be set
     */
    virtual void setActive(bool active);

    private:

    /** the consituent camera controllers */
    std::vector<CameraController*> cameraControllers;

};

}

#endif
