/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/Output.cpp))
 */

#ifndef _OUTPUT_HH_
#define _OUTPUT_HH_

#include "Input.hh"

namespace hardware {

/**
 *
 * @author Derek Bankieris
 *
 * reprents an {@link Input} which has been processed for ouput as a command
 * from a controller. An <code>Output</code> scales its corresponding
 * <code>Input<code> to fit within the <code>Output</code>'s bounds as defined
 * by <code>getMinimumValue()</code>, <code>getMaximumValue()</code>, and
 * <code>getNeutralValue()</code>, and provides support for further processing,
 * such as dead-bands and inversion.
 */
class Output {

    public:

    /** destructs this instance */
    virtual ~Output() {};

    /**
     * constructs a new, non-inverting instance with a range of
     * </code>[-1, 1]</code> and neutral point of <code>0</code>
     *
     * @oaran input the input that this output is to process
     */
    Output(Input& input);

    /**
     * sets the input that this output is to process
     *
     * @param input the input to be processed by this output
     */
    void setInput(Input& input);

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
    bool isInverted();

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its minimum (or maximum), as determined by
     * <code>Input::getMinimumValue()</code>
     * (or <code>Input::getMaximumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the minimum value that this output can return
     */
    double getMinimumValue();

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its maximum (or minimum), as determined by
     * <code>Input::getMaximumValue()</code>
     * (or <code>Input::getMinimumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the maximum value that this output can return
     */
    double getMaximumValue();

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its neutral point, as determined by
     * <code>Input::getNeutralValue()</code>
     *
     * returns the neutral value of this output
     */
    double getNeutralValue();

    /**
     * returns the value of the this instances <code>Input</code>
     * scaled to [<code>getMinimumValue()</code>,
     * <code>getMaximumValue()</code>], with a neutral
     * value of <code>getNeutralValue()</code>
     *
     * @return the processed value
     */
    double getValue();

    private:

    /**
     * the correpsonding input that this output will process and derive its
     * value from
     */
    Input *input;

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

};

}

#endif
