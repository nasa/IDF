/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/SingleInput.cpp))
 */

#ifndef _SINGLE_INPUT_HH_
#define _SINGLE_INPUT_HH_

#include "Input.hh"

namespace idf {

/**
 * represents a single degree of freedom or a single dimension of a device's
 * set of controls. For example, a <code>SingleInput<code> could be used to
 * represent a single button, one axis of a joystick, a slider, or a trigger.
 * To combine multiple controls into one {@link Input}, see
 * {@link CompositeInput}.
 *
 * @author Derek Bankieris
 */
class SingleInput : public Input {

    public:

    /**
     * constructs a new instance with a neutral value of
     * <code>(min + max) / 2</code>
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     */
    SingleInput(double minimum, double maximum);

    /**
     * constructs a new instance
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     * @param neutral the neutral value
     */
    SingleInput(double minimum, double maximum, double neutral);

    /**
     * returns the minimum value this input can take
     *
     * @return the minimum possible value
     */
    virtual double getMinimumValue();

    /**
     * returns the neutral value
     *
     * @return the neutral value
     */
    virtual double getNeutralValue();

    /**
     * returns the maximum value this input can take
     *
     * @return the maximum possible value
     */
    virtual double getMaximumValue();

    /**
     * returns the value
     *
     * @return the value
     */
    virtual double getValue();

    /**
     * sets the value, which should be a raw input value from the device
     * driving this input
     *
     * @param value the input value
     */
    void setValue(double value);

    protected:

    /** the minimum value */
    double minimum;

    /** the neutral value */
    double neutral;

    /** the maximum value */
    double maximum;

    /** the current value */
    double value;

    private:

    /**
     * initializes this instance's values
     *
     * @param min the minimum value
     * @param max the maximum value
     * @param neutral the neutral value
     */
    void initialize(double minimum, double maximum, double neutral);

};

}

#endif

