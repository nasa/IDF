/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/SingleCameraController.cpp))
 */

#ifndef _SINGLE_CAMERA_CONTROLLER_HH_
#define _SINGLE_CAMERA_CONTROLLER_HH_

#include "CameraController.hh"
#include "inputAbstraction/include/Output.hh"
#include "inputAbstraction/include/Input.hh"

namespace idf {

/**
 * represents a single camera controller
 *
 * @author Derek Bankieris
 */
class SingleCameraController : public CameraController {

    public:

    /** pan */
    Output pan;

    /** tilt */
    Output tilt;

    /** spin */
    Output spin;

    /** zoom */
    Output zoom;

    /**
     * constructs a new instance using the specified inputs
     *
     * @param pan the input to process as pan
     * @param tilt the input to process as tilt
     * @param spin the input to process as spin
     * @param zoom the input to process as zoom
     */
    SingleCameraController(Input& pan, Input& tilt, Input& spin, Input& zoom);

    virtual ~SingleCameraController() {};

    virtual double getPan();
    virtual double getTilt();
    virtual double getSpin();
    virtual double getZoom();

    void setPan(Input& pan);
    void setTilt(Input& tilt);
    void setSpin(Input& spin);
    void setZoom(Input& zoom);

};

}

#endif
