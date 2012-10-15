#ifndef _FLIGHT_CONTROLLER_HH_
#define _FLIGHT_CONTROLLER_HH_

namespace idf {

/**
 * represents the interface that an input device must satisfy to qualify as a
 * flight controller device
 *
 * @author Derek Bankieris
 */
class FlightController {

    public:

    /** destructor */
    virtual ~FlightController() {};

    /**
     * returns the commanded roll
     *
     * @return the roll command
     */
    virtual double getRoll() = 0;

    /**
     * returns the commanded pitch
     *
     * @return the pitch command
     */
    virtual double getPitch() = 0;

    /**
     * returns the commanded yaw
     *
     * @return the yaw command
     */
    virtual double getYaw() = 0;

    /**
     * returns the commanded x
     *
     * @return the x command
     */
    virtual double getX() = 0;

    /**
     * returns the commanded y
     *
     * @return the y command
     */
    virtual double getY() = 0;

    /**
     * returns the commanded z
     *
     * @return the z command
     */
    virtual double getZ() = 0;

};

}

#endif
