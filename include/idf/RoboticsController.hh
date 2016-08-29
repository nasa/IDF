/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RoboticsController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RoboticsController.cpp}
 */

#ifndef _ROBOTICS_CONTROLLER_HH_
#define _ROBOTICS_CONTROLLER_HH_

#include "idf/Controller.hh"

namespace idf {

/**
 * interface that an input device must satisfy to qualify as a robotics controller
 *
 * @author Derek Bankieris
 */
class RoboticsController : public Controller {

    public:

    /** destructor */
    virtual ~RoboticsController() {};

    virtual void setActive(bool active);

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

    /**
     * when active, returns the commanded trigger state. When inactive, returns @c false.
     *
     * @return the trigger command
     */
    bool getTrigger() const;

    /**
     * when active, returns the commanded rate mode. When inactive, returns the last commanded rate mode.
     *
     * @return the rate mode command
     */
    bool getRateMode() const;

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

    /**
     * returns the commanded trigger state
     *
     * @return the trigger command
     */
    virtual bool getCommandedTrigger() const = 0;

    /**
     * returns the commanded rate mode
     *
     * @return the rate mode command
     */
    virtual bool getCommandedRateMode() const = 0;

    private:

    /** the rate mode returned by getRateMode() when inactive */
    bool inactiveRateMode;

};

}

#endif
