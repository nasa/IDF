/**
 * @trick_parse{everything}
 * @trick_link_dependency{simulationInterface/src/FlightController.cpp}
 */

#ifndef _FLIGHT_CONTROLLER_HH_
#define _FLIGHT_CONTROLLER_HH_

#include "simulationInterface/include/Controller.hh"

namespace idf {

/**
 * interface that an input device must satisfy to qualify as a flight controller
 *
 * @author Derek Bankieris
 */
class FlightController : public Controller {

    public:

    /** destructor */
    virtual ~FlightController() {};

    /**
     * when active, returns the commanded roll normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the roll command
     */
    double getRoll() const;

    /**
     * when active, returns the commanded pitch normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the pitch command
     */
    double getPitch() const;

    /**
     * when active, returns the commanded yaw normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the yaw command
     */
    double getYaw() const;

    /**
     * when active, returns the commanded x normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the x command
     */
    double getX() const;

    /**
     * when active, returns the commanded y normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the y command
     */
    double getY() const;

    /**
     * when active, returns the commanded z normalized to [-1, 0, 1]. When inactive, returns 0.
     *
     * @return the z command
     */
    double getZ() const;

    protected:

    /**
     * returns the commanded roll normalized to [-1, 0, 1]
     *
     * @return the roll command
     */
    virtual double getCommandedRoll() const = 0;

    /**
     * returns the commanded pitch normalized to [-1, 0, 1]
     *
     * @return the pitch command
     */
    virtual double getCommandedPitch() const = 0;

    /**
     * returns the commanded yaw normalized to [-1, 0, 1]
     *
     * @return the yaw command
     */
    virtual double getCommandedYaw() const = 0;

    /**
     * returns the commanded x normalized to [-1, 0, 1]
     *
     * @return the x command
     */
    virtual double getCommandedX() const = 0;

    /**
     * returns the commanded y normalized to [-1, 0, 1]
     *
     * @return the y command
     */
    virtual double getCommandedY() const = 0;

    /**
     * returns the commanded z normalized to [-1, 0, 1]
     *
     * @return the z command
     */
    virtual double getCommandedZ() const = 0;

};

}

#endif
