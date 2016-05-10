/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/Output.cpp))
 */

#ifndef _OUTPUT_HH_
#define _OUTPUT_HH_

#include <vector>

#include "inputAbstraction/include/Deadbandable.hh"
#include "inputAbstraction/include/Input.hh"

namespace idf {

/**
 * reprents an {@link Input} which has been processed for ouput as a command
 * from a controller. An <code>Output</code> scales its corresponding
 * <code>Input<code> to fit within the <code>Output</code>'s bounds as defined
 * by <code>getMinimumValue()</code>, <code>getMaximumValue()</code>, and
 * <code>getNeutralValue()</code>, and provides support for further processing,
 * such as dead-bands and inversion.
 *
 * @author Derek Bankieris
 */
class Output : public Deadbandable {

    public:

    /**
     * constructs a new, non-inverting instance with a range of
     * </code>[-1, 1]</code> and neutral point of <code>0</code>
     *
     * @param input the input that this output will process
     */
    Output(const Input& input);

    /**
     * sets the input that this output will process
     *
     * @param input the input to be processed by this output
     */
    void setInput(const Input& input);

    /**
     * sets the range to which this output will scale its input's value
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     * @param neutral the neutral value
     */
    void setRange(double minimum, double maximum, double neutral);

    /**
     * sets the range to which this output will scale its input's value, with
     * a neutral value of <code>(minimum + maximum) / 2</code>
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     */
    void setRange(double minimum, double maximum);

    /**
     * sets whether or not this output inverts its input
     *
     * @param inverted the inverted state of this output
     */
    void setInverted(bool inverted);

    /**
     * returns whether or not this output inverts its input
     *
     * @return the inverted state of this output
     */
    bool isInverted() const;

    /**
     * sets whether or not this output acts as a toggle switch. A toggle output
     * returns only the extemeties of its range (minimum or maximum value) and
     * alternates between the two every time its true value rises through its
     * neutral point.
     *
     * @param toggle the toggle state of this output
     */
    void setToggle(bool toggle);

    /**
     * returns whether or not this output acts as a toggle switch. A toggle
     * output returns only the extemeties of its range (minimum or maximum
     * value) and alternates between the two every time its true value rises
     * through its neutral point.
     *
     * @return the toggle state of this output
     */
    bool isToggle() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its minimum (or maximum), as determined by
     * <code>Input::getMinimumValue()</code>
     * (or <code>Input::getMaximumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the minimum value that this output can return
     */
    double getMinimumValue() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its maximum (or minimum), as determined by
     * <code>Input::getMaximumValue()</code>
     * (or <code>Input::getMinimumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the maximum value that this output can return
     */
    double getMaximumValue() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its neutral point, as determined by
     * <code>Input::getNeutralValue()</code>
     *
     * returns the neutral value of this output
     */
    double getNeutralValue() const;

    /**
     * returns the value of the this instance's <code>Input</code>
     * scaled to [<code>getMinimumValue()</code>,
     * <code>getMaximumValue()</code>], with a neutral
     * value of <code>getNeutralValue()</code>, and inverted as specified by
     * <code>isInverted()</code>
     *
     * @return the processed value
     */
    double getValue() const;

    /**
     * returns the value of the this instance's <code>Input</code> normalized to
     * <code>[-1, 0, 1]</code> and inverted as specified by
     * <code>isInverted()</code>
     *
     * @return the normalized and possibly inverted value
     */
    double getNormalizedValue() const;

    private:

    /**
     * the correpsonding input that this output will process and derive its
     * value from
     */
    const Input *input;

    /**
     * the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its minimum (or maximum), as determined by
     * <code>Input::getMinimumValue()</code>
     * (or <code>Input::getMaximumValue()</code>), as specified by
     * <code>isInverted()</code>
     */
    double minimum;

    /**
     * the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its maximum (or minimum), as determined by
     * <code>Input::getMaximumValue()</code>
     * (or <code>Input::getMinimumValue()</code>), as specified by
     * <code>isInverted()</code>
     */
    double maximum;

    /**
     * the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its neutral point, as determined by
     * <code>Input::getNeutralValue()</code>
     */
    double neutral;

    /**
     * inverts the mapping between this output and its corresponding input
     * about the neutral point
     */
    bool inverted;

    /**
     * causes this output to act as a toggle switch. A toggle output returns
     * only either the <code>minimum</code> or <code>maximum</code> value, and
     * switches when its true value rises through <code>neutral</code>.
     */
    bool toggle;

    /** the value to return when acting as a toggle switch */
    mutable double toggleValue;

    /** used to determine when to toggle, if enabled */
    mutable double lastValue;

};

}

#endif
