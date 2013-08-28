/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeFlightController.cpp))
 */

#ifndef _COMPOSITE_FLIGHT_CONTROLLER_HH_
#define _COMPOSITE_FLIGHT_CONTROLLER_HH_

#include "CompositeController.hh"
#include "FlightController.hh"

namespace idf {

#ifdef SWIG
%template(CompositeControllerFlightController) CompositeController<FlightController>;
#endif

/**
 * combines multiple <code>FlightController</code>s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeFlightController : public CompositeController<FlightController> {

    public:

    /**
     * gets the conglomerate roll value, normalized to [-1, 0, 1]
     *
     * @return the combined roll of all added flight controllers
     */
    double getCommandedRoll() const;

    /**
     * gets the conglomerate pitch value, normalized to [-1, 0, 1]
     *
     * @return the combined pitch of all added flight controllers
     */
    double getCommandedPitch() const;

    /**
     * gets the conglomerate yaw value, normalized to [-1, 0, 1]
     *
     * @return the combined yaw of all added flight controllers
     */
    double getCommandedYaw() const;

    /**
     * gets the conglomerate x value, normalized to [-1, 0, 1]
     *
     * @return the combined x of all added flight controllers
     */
    double getCommandedX() const;

    /**
     * gets the conglomerate y value, normalized to [-1, 0, 1]
     *
     * @return the combined y of all added flight controllers
     */
    double getCommandedY() const;

    /**
     * gets the conglomerate z value, normalized to [-1, 0, 1]
     *
     * @return the combined z of all added flight controllers
     */
    double getCommandedZ() const;

};

}

#endif
