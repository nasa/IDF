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
#include "inputAbstraction/include/CompositeInput.hh"
#include "inputAbstraction/include/WingMan.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"
#include "inputAbstraction/include/Gravis.hh"

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
     * returns the commanded roll, normalized to [-1, 0, 1]
     *
     * @return the roll command
     */
    virtual double getCommandedRoll();

    /**
     * returns the commanded pitch, normalized to [-1, 0, 1]
     *
     * @return the pitch command
     */
    virtual double getCommandedPitch();

    /**
     * returns the commanded yaw, normalized to [-1, 0, 1]
     *
     * @return the yaw command
     */
    virtual double getCommandedYaw();

    /**
     * returns the commanded x, normalized to [-1, 0, 1]
     *
     * @return the x command
     */
    virtual double getCommandedX();

    /**
     * returns the commanded y, normalized to [-1, 0, 1]
     *
     * @return the y command
     */
    virtual double getCommandedY();

    /**
     * returns the commanded z, normalized to [-1, 0, 1]
     *
     * @return the z command
     */
    virtual double getCommandedZ();

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

    /**
     * creates a new <code>SingleFlightController</code> mapped to
     * <code>gravis</code> using appropriate defaults
     *
     * @param gravis the inputs to use in the default mapping
     *
     * @return a new Gravis-based flight controller
     */
    static SingleFlightController* createInstance(Gravis& gravis);

};

}

#endif
