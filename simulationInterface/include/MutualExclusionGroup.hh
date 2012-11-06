/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/MutualExclusionGroup.cpp))
 */

#ifndef __MUTUAL_EXCLUSION_GROUP_HH_
#define __MUTUAL_EXCLUSION_GROUP_HH_

#include <vector>

#include "StateChangeListener.hh"
#include "Controller.hh"

namespace idf {

/**
 * manages the states of a collection of {@link Controller}s, enforcing
 * mutual exclusivity of their operation by ensuring that at most one is active
 * at any time
 *
 * @author Derek Bankieris
 */
class MutualExclusionGroup : public StateChangeListener {

    public:

    /** destructor */
    virtual ~MutualExclusionGroup() {}

    /**
     * causes <code>controller</code>'s operation to be mutually exclusive with
     * all other controllers managed by this instance. Adding a controller that
     * is already being managed has no effect.
     *
     * @param controller the controller to manage
     */
    virtual void add(Controller& controller);

    /**
     * causes <code>controller</code>'s operation to no longer be mutually
     * exclusive with all other controllers managed by this instance. Removing
     * a controller that is not being managed has no effect.
     *
     * @param controller the controller to stop managing
     */
    virtual void remove(const Controller& controller);

    /**
     * called in response to a change in state of a <code>Controller</code>
     * for which this instance is registered
     *
     * @param controller the controller whose state has changed
     */
    virtual void stateChanged(Controller& controller);

    protected:

    /** the controllers being managed by this instance */
    std::vector<Controller*> controllers;

    /**
     * disables all controllers being managed by this instance other than
     * <code>activeController</code>
     *
     * @param activeController the only controller not to disable
     */
    void disableOtherControllers(const Controller& activeController);

};

}

#endif
