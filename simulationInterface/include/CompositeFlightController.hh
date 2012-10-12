/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeFlightController.cpp))
 */

#ifndef _COMPOSITE_FLIGHT_CONTROLLER_HH_
#define _COMPOSITE_FLIGHT_CONTROLLER_HH_

#include <vector>
#include "FlightController.hh"

namespace hardware {

/**
 * combines multiple <code>FlightController</code>s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeFlightController : public FlightController {

    public:

    /**
     * adds <code>flightController</code>, combining its values with all other
     * added <code>FlightController</code>s
     */
    void addFlightController(FlightController& flightController);

    /**
     * removes <code>flightController</code>, no longer combining its values
     * with other <code>FlightController</code>s
     */
    void removeFlightController(FlightController& flightController);

    /**
     * gets the conglomerate roll value
     *
     * @return the combined roll of all added flight controllers
     */
    double getRoll();

    /**
     * gets the conglomerate pitch value
     *
     * @return the combined pitch of all added flight controllers
     */
    double getPitch();

    /**
     * gets the conglomerate yaw value
     *
     * @return the combined yaw of all added flight controllers
     */
    double getYaw();

    /**
     * gets the conglomerate x value
     *
     * @return the combined x of all added flight controllers
     */
    double getX();

    /**
     * gets the conglomerate y value
     *
     * @return the combined y of all added flight controllers
     */
    double getY();

    /**
     * gets the conglomerate z value
     *
     * @return the combined z of all added flight controllers
     */
    double getZ();

    private:

    /** the consituent flight controllers */
    std::vector<FlightController*> flightControllers;

    /**
     * bounds <code>result</code> to [-1, 1]
     *
     * @param result the result to bound
     *
     * @return the bounded result
     */
    static double boundResult(double result);

};

}

#endif
