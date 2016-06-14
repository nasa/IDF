/*
PURPOSE:
*/

/** @trick_parse{everything} */

#ifndef _COMPOSITE_CONTROLLER_HH_
#define _COMPOSITE_CONTROLLER_HH_

#include <vector>
#include <algorithm>

#include "simulationInterface/include/Controller.hh"

namespace idf {

/**
 * combines multiple @a T's into a single entity, implementing the composite design pattern.
 * @a T must derive from Controller.
 *
 * @param T the constituent type
 *
 * @author Derek Bankieris
 */
template <class T>
class CompositeController : public T {

    public:

    /** destructor */
    virtual ~CompositeController() {}

    /**
     * adds @a component. Adding a component that is already contained by this instance has no effect.
     *
     * @param component the component to be added
     */
    virtual void add(T& component) {
        // Add the component, if not present.
        if(std::find(components.begin(), components.end(), &component) == components.end()) {
            components.push_back(&component);
        }
    }

    /**
     * removes @a component. Removing a component that is not contained by this instance has no effect.
     *
     * @param component the componnet to be removed
     */
    virtual void remove(const T& component) {
        // Remove the component, if present.
        components.erase(std::remove(components.begin(), components.end(), &component), components.end());
    }

    /**
     * sets the active state of this controller and all consituent controllers and notifies all registered
     * listeners of any change. Inactive controllers output neutral or default values when polled.
     *
     * @param activate the state to be set
     */
    virtual void setActive(bool activate) {
        // Set all constituent controller's states.
        for (typename std::vector<T*>::iterator i = components.begin(); i != components.end(); ++i) {
            (*i)->setActive(activate);
        }

        // Call the parent method to set this instance's state.
        Controller::setActive(activate);
    }

    protected:

    /** the consituent components */
    std::vector<T*> components;

};

}

#endif
