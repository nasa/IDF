/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/SingleInput.cpp}
 */

#ifndef _SINGLE_INPUT_HH_
#define _SINGLE_INPUT_HH_

#include "inputAbstraction/include/Deadbandable.hh"
#include "inputAbstraction/include/Input.hh"

namespace idf {

/**
 * represents a single degree of freedom or a single dimension of a device's set of controls.
 * For example, a %SingleInput could be used to represent a single button, one axis of a joystick,
 * a slider, or a trigger. To combine multiple controls into one Input, see CompositeInput.
 *
 * @author Derek Bankieris
 */
class SingleInput : public Input, public Deadbandable {

    public:

    /**
     * constructs a new instance with a neutral value of <code>(min + max) / 2</code>
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
     * configures this instance's values, using a neutral value of <code>(minimum + maximum) / 2</code>
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     *
     * @throws std::logic_error if <code>minimum > maximum</code>
     */
    void configure(double minimum, double maximum);

    /**
     * configures this instance's values
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     * @param neutral the neutral value
     *
     * @throws std::logic_error if <code>minimum <= neutral <= maximum</code> is not @c true
     */
    void configure(double minimum, double maximum, double neutral);

    /**
     * returns the minimum value this input can take
     *
     * @return the minimum possible value
     */
    double getMinimumValue() const;

    /**
     * returns the neutral value
     *
     * @return the neutral value
     */
    double getNeutralValue() const;

    /**
     * returns the maximum value this input can take
     *
     * @return the maximum possible value
     */
    double getMaximumValue() const;

    /**
     * returns the value
     *
     * @return the value
     */
    double getValue() const;

    /**
     * sets the value, which should be a raw input value from the device driving this input
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

};

}

#endif

