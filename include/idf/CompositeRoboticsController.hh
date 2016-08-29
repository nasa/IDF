/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CompositeRoboticsController.cpp)
(idf/Utils.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CompositeRoboticsController.cpp}
 * @trick_link_dependency{idf/Utils.cpp}
 */

#ifndef COMPOSITE_ROBOTICS_CONTROLLER_HH
#define COMPOSITE_ROBOTICS_CONTROLLER_HH

#include "idf/CompositeController.hh"
#include "idf/RoboticsController.hh"

namespace idf {

#ifdef SWIG
%template(CompositeControllerRoboticsController) CompositeController<RoboticsController>;
#endif

/**
 * combines multiple {@link RoboticsController}s into a single entity,
 * superimposing their values. Resulting values are restricted to [-1, 1].
 *
 * @author Derek Bankieris
 */
class CompositeRoboticsController : public CompositeController<RoboticsController> {

    public:

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

};

}

#endif
