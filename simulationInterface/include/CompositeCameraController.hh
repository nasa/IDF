/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeCameraController.cpp))
 */

#ifndef _COMPOSITE_CAMERA_CONTROLLER_HH_
#define _COMPOSITE_CAMERA_CONTROLLER_HH_

#include <vector>
#include "CameraController.hh"

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
     * added <code>CameraController</code>s
     */
    void addCameraController(CameraController& cameraController);

    /**
     * removes <code>cameraController</code>, no longer combining its values
     * with other <code>CameraController</code>s
     */
    void removeCameraController(CameraController& cameraController);

    /**
     * gets the conglomerate pan value
     *
     * @return the combined pan of all added camera controllers
     */
    double getPan();

    /**
     * gets the conglomerate tilt value
     *
     * @return the combined tilt of all added camera controllers
     */
    double getTilt();

    /**
     * gets the conglomerate spin value
     *
     * @return the combined spin of all added camera controllers
     */
    double getSpin();

    /**
     * gets the conglomerate zoom value
     *
     * @return the combined zoom of all added camera controllers
     */
    double getZoom();

    private:

    /** the consituent camera controllers */
    std::vector<CameraController*> cameraControllers;

    /**
     * bounds <code>result</code> to [-1, 1]
     *
     * @param result the result to bound
     *
     * @return the bounded result
     */
    static double boundResult(double result);

};

}

#endif
