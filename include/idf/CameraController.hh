/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CameraController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CameraController.cpp}
 */

#ifndef CAMERA_CONTROLLER_HH
#define CAMERA_CONTROLLER_HH

#include "idf/Controller.hh"

namespace idf {

/**
 * interface that an input device must satisfy to qualify as a camera controller
 *
 * @author Derek Bankieris
 */
class CameraController : public Controller {

    public:

    /** destructor */
    virtual ~CameraController() {};

    /**
     * when active, returns the commanded pan normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the pan command
     */
    double getPan() const;

    /**
     * when active, returns the commanded tilt normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the tilt command
     */
    double getTilt() const;

    /**
     * when active, returns the commanded spin normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the spin command
     */
    double getSpin() const;

    /**
     * when active, returns the commanded zoom normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the zoom command
     */
    double getZoom() const;

    protected:

    /**
     * returns the commanded pan normalized to [-1, 0, 1]
     *
     * @return the pan command
     */
    virtual double getCommandedPan() const = 0;

    /**
     * returns the commanded tilt normalized to [-1, 0, 1]
     *
     * @return the tilt command
     */
    virtual double getCommandedTilt() const = 0;

    /**
     * returns the commanded spin normalized to [-1, 0, 1]
     *
     * @return the spin command
     */
    virtual double getCommandedSpin() const = 0;

    /**
     * returns the commanded zoom normalized to [-1, 0, 1]
     *
     * @return the zoom command
     */
    virtual double getCommandedZoom() const = 0;

};

}

#endif
