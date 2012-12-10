/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeFlightController.cpp))
 */

#ifndef _COMPOSITE_FLIGHT_CONTROLLER_HH_
#define _COMPOSITE_FLIGHT_CONTROLLER_HH_

#include "FlightController.hh"
#include <vector>

namespace idf {

/**
 * combines multiple <code>FlightController</code>s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeFlightController : public FlightController {

    public:

    /** destructor */
    ~CompositeFlightController() {}

    /**
     * adds <code>flightController</code>, combining its values with all other
     * added <code>FlightController</code>s. Adding a controller that is
     * already contained by this instance has no effect.
     */
    virtual void add(FlightController& flightController);

    /**
     * removes <code>flightController</code>, no longer combining its values
     * with other <code>FlightController</code>s. Removing a controller
     * that is not contained by this instance has no effect.
     */
    virtual void remove(const FlightController& flightController);

    /**
     * gets the conglomerate roll value, normalized to [-1, 0, 1]
     *
     * @return the combined roll of all added flight controllers
     */
    virtual double getCommandedRoll() const;

    /**
     * gets the conglomerate pitch value, normalized to [-1, 0, 1]
     *
     * @return the combined pitch of all added flight controllers
     */
    virtual double getCommandedPitch() const;

    /**
     * gets the conglomerate yaw value, normalized to [-1, 0, 1]
     *
     * @return the combined yaw of all added flight controllers
     */
    virtual double getCommandedYaw() const;

    /**
     * gets the conglomerate x value, normalized to [-1, 0, 1]
     *
     * @return the combined x of all added flight controllers
     */
    virtual double getCommandedX() const;

    /**
     * gets the conglomerate y value, normalized to [-1, 0, 1]
     *
     * @return the combined y of all added flight controllers
     */
    virtual double getCommandedY() const;

    /**
     * gets the conglomerate z value, normalized to [-1, 0, 1]
     *
     * @return the combined z of all added flight controllers
     */
    virtual double getCommandedZ() const;

    /**
     * sets the active state of this controller and all consituent controllers
     * and notifies all registered listeners of any change. Inactive controllers
     * output neutral or default values when polled.
     *
     * @param active the state to be set
     */
    virtual void setActive(bool active);

    protected:

    /** the consituent flight controllers */
    std::vector<FlightController*> flightControllers;


};

}

#endif
