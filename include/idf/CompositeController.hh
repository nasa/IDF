/*
PURPOSE:
*/

/** @trick_parse{everything} */

#ifndef COMPOSITE_CONTROLLER_HH
#define COMPOSITE_CONTROLLER_HH

#include <algorithm>
#include <functional>
#include <vector>

#include "idf/Controller.hh"

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
     * sets the active state of this controller and all constituent controllers and notifies all registered
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

    /** the constituent components */
    std::vector<T*> components;

    /**
     * accumates a field across all constituents
     *
     * @param accessor the accessor returning the field to be accumulated
     * @param function a functor or function pointer that takes two
     *   arguments and returns one value, all of accessor's type, used to
     *   sequentially accumulate the fields
     *
     * @return the accumulated value
     */
    #ifndef SWIG
    template<class U, class BinaryOperation>
    U accumulate(U (T::*accessor)() const, const BinaryOperation& function) const {
        U result = U();
        for (typename std::vector<T*>::const_iterator i = components.begin(); i != components.end(); ++i) {
            result = function(result, ((*i)->*accessor)());
        }
        return result;
    }
    #endif

};

}

#endif
