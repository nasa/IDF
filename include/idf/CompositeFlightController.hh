/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CompositeFlightController.cpp)
(idf/Utils.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CompositeFlightController.cpp}
 * @trick_link_dependency{idf/Utils.cpp}
 */

#ifndef COMPOSITE_FLIGHT_CONTROLLER_HH
#define COMPOSITE_FLIGHT_CONTROLLER_HH

#include "idf/CompositeController.hh"
#include "idf/FlightController.hh"

namespace idf {

#ifdef SWIG
%template(CompositeControllerFlightController) CompositeController<FlightController>;
#endif

/**
 * combines multiple {@link FlightController}s into a single entity,
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

    /**
     * gets the conglomerate trigger value, which is the logical
     * OR of all constituent controllers' trigger values
     *
     * @return the combined trigger of all added robotics controllers
     */
    bool getCommandedTrigger() const;

    /**
     * returns the commanded Comm
     *
     * @return the Comm command
     */
    bool getCommandedComm() const;
    
    /**
     * returns the commanded shutdown
     *
     * @return the shutdown command
     */
    bool getCommandedShutdown() const;

};

}

#endif
