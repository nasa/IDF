/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/CompositeRoboticsController.cpp))
 */

#ifndef _COMPOSITE_ROBOTICS_CONTROLLER_HH_
#define _COMPOSITE_ROBOTICS_CONTROLLER_HH_

#include "RoboticsController.hh"
#include <vector>

namespace idf {

/**
 * combines multiple <code>RoboticsController</code>s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeRoboticsController : public RoboticsController {

    public:

    /** destructor */
    ~CompositeRoboticsController() {}

    /**
     * adds <code>roboticsController</code>, combining its values with all other
     * added <code>RoboticsController</code>s. Adding a controller that is
     * already contained by this instance has no effect.
     */
    void add(RoboticsController& roboticsController);

    /**
     * removes <code>roboticsController</code>, no longer combining its values
     * with other <code>RoboticsController</code>s. Removing a controller
     * that is not contained by this instance has no effect.
     */
    void remove(const RoboticsController& roboticsController);

    /**
     * gets the conglomerate roll value, normalized to [-1, 0, 1]
     *
     * @return the combined roll of all added robotics controllers
     */
    double getCommandedRoll() const;

    /**
     * gets the conglomerate pitch value, normalized to [-1, 0, 1]
     *
     * @return the combined pitch of all added robotics controllers
     */
    double getCommandedPitch() const;

    /**
     * gets the conglomerate yaw value, normalized to [-1, 0, 1]
     *
     * @return the combined yaw of all added robotics controllers
     */
    double getCommandedYaw() const;

    /**
     * gets the conglomerate x value, normalized to [-1, 0, 1]
     *
     * @return the combined x of all added robotics controllers
     */
    double getCommandedX() const;

    /**
     * gets the conglomerate y value, normalized to [-1, 0, 1]
     *
     * @return the combined y of all added robotics controllers
     */
    double getCommandedY() const;

    /**
     * gets the conglomerate z value, normalized to [-1, 0, 1]
     *
     * @return the combined z of all added robotics controllers
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
     * gets the conglomerate rate mode value, which is the logical
     * OR of all constituent controllers' rate mode values
     *
     * @return the combined rate mode of all added robotics controllers
     */
    bool getCommandedRateMode() const;

    /**
     * sets the active state of this controller and all consituent controllers
     * and notifies all registered listeners of any change. Inactive controllers
     * output neutral or default values when polled.
     *
     * @param active the state to be set
     */
    void setActive(bool active);

    protected:

    /** the consituent robotics controllers */
    std::vector<RoboticsController*> roboticsControllers;


};

}

#endif
