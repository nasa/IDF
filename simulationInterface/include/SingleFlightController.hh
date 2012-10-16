/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/SingleFlightController.cpp))
 */

#ifndef _SINGLE_FLIGHT_CONTROLLER_HH_
#define _SINGLE_FLIGHT_CONTROLLER_HH_

#include "FlightController.hh"
#include "inputAbstraction/include/Output.hh"
#include "inputAbstraction/include/Input.hh"
#include "inputAbstraction/include/WingMan.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"
#include "inputAbstraction/include/CompositeInput.hh"

namespace idf {

/**
 * represents a single flight controller
 *
 * @author Derek Bankieris
 */
class SingleFlightController : public FlightController {

    public:

    /** roll */
    Output roll;

    /** pitch */
    Output pitch;

    /** yaw */
    Output yaw;

    /** x */
    Output x;

    /** y */
    Output y;

    /** z */
    Output z;

    /**
     * constructs a new instance using the specified inputs
     *
     * @param roll the input to process as roll
     * @param pitch the input to process as pitch
     * @param yaw the input to process as yaw
     * @param x the input to process as x
     * @param y the input to process as y
     * @param z the input to process as z
     */
    SingleFlightController(
      Input& roll, Input& pitch, Input& yaw,
      Input& x, Input& y, Input& z);

    /** destructor */
    virtual ~SingleFlightController() {};

    /**
     * returns the commanded roll
     *
     * @return the roll command
     */
    virtual double getRoll();

    /**
     * returns the commanded pitch
     *
     * @return the pitch command
     */
    virtual double getPitch();

    /**
     * returns the commanded yaw
     *
     * @return the yaw command
     */
    virtual double getYaw();

    /**
     * returns the commanded x
     *
     * @return the x command
     */
    virtual double getX();

    /**
     * returns the commanded y
     *
     * @return the y command
     */
    virtual double getY();

    /**
     * returns the commanded z
     *
     * @return the z command
     */
    virtual double getZ();

    /**
     * creates a new <code>SingleFlightController</code> mapped to
     * <code>wingMan</code> using appropriate defaults
     *
     * @param wingMan the inputs to use in the default mapping
     *
     * @return a new WingMan-based flight controller
     */
    static SingleFlightController* createInstance(WingMan& wingMan);

    /**
     * creates a new <code>SingleFlightController</code> mapped to
     * <code>spaceExplorer</code> using appropriate defaults
     *
     * @param spaceExplorer the inputs to use in the default mapping
     *
     * @return a new SpaceExplorer-based flight controller
     */
    static SingleFlightController* createInstance(SpaceExplorer& spaceExplorer);

    /**
     * creates a new <code>SingleFlightController</code> mapped to
     * <code>spaceNavigator</code> using appropriate defaults
     *
     * @param spaceNavigator the inputs to use in the default mapping
     *
     * @return a new SpaceNavigator-based flight controller
     */
    static SingleFlightController* createInstance(SpaceNavigator& spaceNavigator);

};

}

#endif
