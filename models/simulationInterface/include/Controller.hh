/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/Controller.cpp))
 */

#ifndef _CONTROLLER_HH_
#define _CONTROLLER_HH_

#include <vector>

#include "StateChangeListener.hh"

namespace idf {

/**
 * abstract base class for all controllers
 *
 * @author Derek Bankieris
 */
class Controller {

    public:

    /** constructor */
    Controller();

    /** destructor */
    virtual ~Controller() = 0;

    /**
     * sets the active state of this controller and notifies all registered
     * listeners of any change. Inactive controllers output neutral or default
     * values when polled.
     *
     * @param active the state to be set
     */
    void setActive(bool active);

    /**
     * gets the active state of this controller. Inactive controllers output
     * neutral or default values when polled.
     *
     * @return the active state
     */
    bool isActive() const;

    /**
     * causes <code>stateChangeListener</code> to be notified when this
     * instance's state changes. Adding a listener that is already registered
     * with this instance has no effect.
     *
     * @stateChangeListener the listener to notify
     */
    virtual void addStateChangeListener(StateChangeListener& stateChangeListener);

    /**
     * causes <code>stateChangeListener</code> to no longer be notified when
     * this instance's state changes. Removing a listener that is not registered
     * with this instance has no effect.
     *
     * @stateChangeListener the listener to stop notifying
     */
    virtual void removeStateChangeListener(const StateChangeListener& stateChangeListener);

    protected:

    /**
     * the general contract of this field is that controllers should output
     * neutral or default values when inactive. It is the responsibility of
     * derived classes to properly implement this behavior.
     */
    bool active;

    /** the listeners to be notified when this instance's state changes */
    std::vector<StateChangeListener*> stateChangeListeners;

};

}

#endif
