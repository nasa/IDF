/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/StateChangeListener.cpp))
 */

#ifndef __STATE_CHANGE_LISTENER_HH_
#define __STATE_CHANGE_LISTENER_HH_

namespace idf {

class Controller;

/**
 * abstract base class representing an interface for receiving notification
 * of state changes of {@link Controller}s
 *
 * @author Derek Bankieris
 */
class StateChangeListener {

    public:

    /** destructor */
    ~StateChangeListener() {}

    /**
     * called in response to a change in state of a <code>Controller</code>
     * for which this instance is registered
     *
     * @param controller the controller whose state has changed
     */
    virtual void stateChanged(Controller& controller) = 0;

};

}

#endif
