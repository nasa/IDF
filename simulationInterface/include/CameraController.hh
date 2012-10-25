/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CameraController.cpp))
 */

#ifndef _CAMERA_CONTROLLER_HH_
#define _CAMERA_CONTROLLER_HH_

#include "Controller.hh"

namespace idf {

/**
 * represents the interface that an input device must satisfy to qualify as a
 * camera controller
 *
 * @author Derek Bankieris
 */
class CameraController : public Controller {

    public:

    /** destructor */
    virtual ~CameraController() {};

    /**
     * when active, returns the commanded pan normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the pan command
     */
    virtual double getPan();

    /**
     * when active, returns the commanded tilt normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the tilt command
     */
    virtual double getTilt();

    /**
     * when active, returns the commanded spin normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the spin command
     */
    virtual double getSpin();

    /**
     * when active, returns the commanded zoom normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the zoom command
     */
    virtual double getZoom();

    protected:

    /**
     * returns the commanded pan normalized to [-1, 0, 1]
     *
     * @return the pan command
     */
    virtual double getCommandedPan() = 0;

    /**
     * returns the commanded tilt normalized to [-1, 0, 1]
     *
     * @return the tilt command
     */
    virtual double getCommandedTilt() = 0;

    /**
     * returns the commanded spin normalized to [-1, 0, 1]
     *
     * @return the spin command
     */
    virtual double getCommandedSpin() = 0;

    /**
     * returns the commanded zoom normalized to [-1, 0, 1]
     *
     * @return the zoom command
     */
    virtual double getCommandedZoom() = 0;

};

}

#endif
