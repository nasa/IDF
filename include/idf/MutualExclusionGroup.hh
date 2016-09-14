/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/MutualExclusionGroup.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/MutualExclusionGroup.cpp}
 */

#ifndef MUTUAL_EXCLUSION_GROUP_HH
#define MUTUAL_EXCLUSION_GROUP_HH

#include <vector>

#include "idf/StateChangeListener.hh"
#include "idf/Controller.hh"

namespace idf {

/**
 * manages the states of a collection of {@link Controller}s, enforcing mutual exclusivity
 * of their operation by ensuring that at most one is active at any time
 *
 * @author Derek Bankieris
 */
class MutualExclusionGroup : public StateChangeListener {

    public:

    /**
     * causes @a controller's operation to be mutually exclusive with all other controllers
     * managed by this instance. Adding a controller that is already being managed has no effect.
     *
     * @param controller the controller to manage
     */
    void add(Controller& controller);

    /**
     * causes @a controller's operation to no longer be mutually exclusive with all other controllers
     * managed by this instance. Removing a controller that is not being managed has no effect.
     *
     * @param controller the controller to stop managing
     */
    void remove(const Controller& controller);

    void stateChanged(Controller& controller);

    protected:

    /** the controllers being managed by this instance */
    std::vector<Controller*> controllers;

    /**
     * disables all controllers being managed by this instance other than @a activeController
     *
     * @param activeController the only controller not to disable
     */
    void disableOtherControllers(const Controller& activeController);

};

}

#endif
