/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/FlightController.cpp))
 */

#ifndef _FLIGHT_CONTROLLER_HH_
#define _FLIGHT_CONTROLLER_HH_

#include "Controller.hh"

namespace idf {

/**
 * represents the interface that an input device must satisfy to qualify as a
 * flight controller
 *
 * @author Derek Bankieris
 */
class FlightController : public Controller {

    public:

    /** destructor */
    virtual ~FlightController() {};

    /**
     * when active, returns the commanded roll normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the roll command
     */
    virtual double getRoll();

    /**
     * when active, returns the commanded pitch normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the pitch command
     */
    virtual double getPitch();

    /**
     * when active, returns the commanded yaw normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the yaw command
     */
    virtual double getYaw();

    /**
     * when active, returns the commanded x normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the x command
     */
    virtual double getX();

    /**
     * when active, returns the commanded y normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the y command
     */
    virtual double getY();

    /**
     * when active, returns the commanded z normalized to [-1, 0, 1].
     * When inactive, returns <code>0</code>.
     *
     * @return the z command
     */
    virtual double getZ();

    protected:

    /**
     * returns the commanded roll normalized to [-1, 0, 1]
     *
     * @return the roll command
     */
    virtual double getCommandedRoll() = 0;

    /**
     * returns the commanded pitch normalized to [-1, 0, 1]
     *
     * @return the pitch command
     */
    virtual double getCommandedPitch() = 0;

    /**
     * returns the commanded yaw normalized to [-1, 0, 1]
     *
     * @return the yaw command
     */
    virtual double getCommandedYaw() = 0;

    /**
     * returns the commanded x normalized to [-1, 0, 1]
     *
     * @return the x command
     */
    virtual double getCommandedX() = 0;

    /**
     * returns the commanded y normalized to [-1, 0, 1]
     *
     * @return the y command
     */
    virtual double getCommandedY() = 0;

    /**
     * returns the commanded z normalized to [-1, 0, 1]
     *
     * @return the z command
     */
    virtual double getCommandedZ() = 0;

};

}

#endif
