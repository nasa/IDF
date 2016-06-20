/** @trick_parse{everything} */

#ifndef _CONTROLLER_HH_
#define _CONTROLLER_HH_

#include <algorithm>
#include <vector>
#include "simulationInterface/include/StateChangeListener.hh"

namespace idf {

template <class T>
struct ControllerTraits;

/**
 * abstract base class for all controllers
 *
 * @author Derek Bankieris
 */
template <class T>
class Controller {

    public:

    /** constructor */
    Controller() :
        active(true) {}

    /** destructor */
    virtual ~Controller() = 0;

    /**
     * sets the active state of this controller and notifies all registered listeners of any change.
     * Inactive controllers output neutral or default values when polled.
     *
     * @param active the state to be set
     */
    virtual void setActive(bool active) {
        if (this->active != active) {
            this->active = active;

            // Notify listeners of state change.
            /*foreach (auto stateChangeListener : stateChangeListeners) {
                stateChangeListener.stateChanged(*this);
            }*/
        }
    }

    /**
     * gets the active state of this controller.
     * Inactive controllers output neutral or default values when polled.
     *
     * @return the active state
     */
    bool isActive() const {
        return active;
    }

    /**
     * causes @a stateChangeListener to be notified when this instance's state changes.
     * Adding a listener that is already registered with this instance has no effect.
     *
     * @param stateChangeListener the listener to notify
     */
    virtual void addStateChangeListener(StateChangeListener& stateChangeListener) {
        // Add the listener, if not present.
        if (std::find(stateChangeListeners.begin(), stateChangeListeners.end(), &stateChangeListener) == stateChangeListeners.end()) {
            stateChangeListeners.push_back(&stateChangeListener);
        }
    }

    /**
     * causes @a stateChangeListener to no longer be notified when this instance's state changes.
     * Removing a listener that is not registered with this instance has no effect.
     *
     * @param stateChangeListener the listener to stop notifying
     */
    virtual void removeStateChangeListener(const StateChangeListener& stateChangeListener) {
        // Remove the listener, if present.
        stateChangeListeners.erase(std::remove(stateChangeListeners.begin(), stateChangeListeners.end(), &stateChangeListener), stateChangeListeners.end());
    }

    template <class V> V getFeature(const typename ControllerTraits<T>::template Feature<V>& feature) const {
        return feature.getValue(static_cast<const T&>(*this));
    }

    protected:

    /**
     * the general contract of this field is that controllers should output neutral or default values
     * when inactive. It is the responsibility of derived classes to properly implement this behavior.
     */
    bool active;

    /** the listeners to be notified when this instance's state changes */
    std::vector<StateChangeListener*> stateChangeListeners;

};

template <class T>
Controller<T>::~Controller() {}

}

#endif
