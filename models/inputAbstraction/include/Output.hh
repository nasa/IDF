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

#include "Input.hh"
#include "Deadband.hh"

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
class Output {

    public:

    /** destructor */
    virtual ~Output() {};

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
    virtual void setInput(const Input& input);

    /**
     * sets the range to which this output will scale its input's value
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     * @param neutral the neutral value
     */
    virtual void setRange(double minimum, double maximum, double neutral);

    /**
     * sets the range to which this output will scale its input's value, with
     * a neutral value of <code>(minimum + maximum) / 2</code>
     *
     * @param minimum the minimum value
     * @param maximum the maximum value
     */
    virtual void setRange(double minimum, double maximum);

    /**
     * sets whether or not this output inverts its input
     *
     * @param inverted the inverted state of this output
     */
    virtual void setInverted(bool inverted);

    /**
     * returns whether or not this output inverts its input
     *
     * @return the inverted state of this output
     */
    virtual bool isInverted() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its minimum (or maximum), as determined by
     * <code>Input::getMinimumValue()</code>
     * (or <code>Input::getMaximumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the minimum value that this output can return
     */
    virtual double getMinimumValue() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its maximum (or minimum), as determined by
     * <code>Input::getMaximumValue()</code>
     * (or <code>Input::getMinimumValue()</code>), as specified by
     * <code>isInverted()</code>
     *
     * returns the maximum value that this output can return
     */
    virtual double getMaximumValue() const;

    /**
     * returns the value <code>getValue()</code> will return when this instance's
     * <code>Input</code>'s value is at its neutral point, as determined by
     * <code>Input::getNeutralValue()</code>
     *
     * returns the neutral value of this output
     */
    virtual double getNeutralValue() const;

    /**
     * returns the value of the this instance's <code>Input</code>
     * scaled to [<code>getMinimumValue()</code>,
     * <code>getMaximumValue()</code>], with a neutral
     * value of <code>getNeutralValue()</code>, and inverted as specified by
     * <code>isInverted()</code>
     *
     * @return the processed value
     */
    virtual double getValue() const;

    /**
     * returns the value of the this instance's <code>Input</code> normalized to
     * <code>[-1, 0, 1]</code> and inverted as specified by
     * <code>isInverted()</code>
     *
     * @return the normalized and possibly inverted value
     */
    virtual double getNormalizedValue() const;

    /**
     * adds <code>deadband</code> to the list of filters. Adding a deadband
     * that is already applied to this instance has no effect.
     *
     * @param deadband the deadband to add
     */
    virtual void addDeadband(const Deadband& deadband);

    /**
     * remove <code>deadband</code> from the list of filters. Removing a
     * deadband that is not applied to this instance has no effect.
     *
     * @param deadband the deadband to remove
     */
    virtual void removeDeadband(const Deadband& deadband);

    /**
     * removes all deadbands applied to this instance
     */
    virtual void clearDeadbands();

    /**
     * returns the deadbands applied to this intance
     *
     * @return the current deadbands
     */
    virtual const std::vector<Deadband>& getDeadbands() const;

    protected:

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

    /** deadband filters */
    std::vector<Deadband> deadbands;

};

}

#endif
