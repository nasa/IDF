/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Output.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Output.cpp}
 */

#ifndef OUTPUT_HH
#define OUTPUT_HH

#include <vector>

#include "idf/Deadbandable.hh"
#include "idf/Input.hh"

namespace idf {

/**
 * reprents an Input which has been processed for ouput as a command from a controller.
 * An %Output scales its corresponding Input to fit within the %Output's bounds as defined
 * by getMinimumValue(), getMaximumValue(), and getNeutralValue(), and provides support
 * for further processing, such as dead-bands and inversion.
 *
 * @author Derek Bankieris
 */
class Output : public Deadbandable {

    public:

    /**
     * constructs a new, non-inverting instance with a range of
     * <code>[-1, 1]</code> and neutral point of @c 0
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
     * returns the value getValue() will return when this instance's Input's value is at its minimum
     * (or maximum), as determined by Input::getMinimumValue() (or Input::getMaximumValue()),
     * as specified by isInverted()
     *
     * returns the minimum value that this output can return
     */
    double getMinimumValue() const;

    /**
     * returns the value getValue() will return when this instance's Input's value is at its maximum
     * (or minimum), as determined by Input::getMaximumValue() (or Input::getMinimumValue()),
     * as specified by isInverted()
     *
     * returns the maximum value that this output can return
     */
    double getMaximumValue() const;

    /**
     * returns the value getValue() will return when this instance's Input's
     * value is at its neutral point, as determined by Input::getNeutralValue()
     *
     * returns the neutral value of this output
     */
    double getNeutralValue() const;

    /**
     * returns the value of the this instance's Input scaled to [getMinimumValue(), getMaximumValue()],
     * with a neutral value of getNeutralValue(), and inverted as specified by isInverted()
     *
     * @return the processed value
     */
    double getValue() const;

    /**
     * returns the value of the this instance's Input normalized to
     * <code>[-1, 0, 1]</code> and inverted as specified by isInverted()
     *
     * @return the normalized and possibly inverted value
     */
    double getNormalizedValue() const;

    private:

    /** the correpsonding input from which this instance will process and derive its value */
    const Input *input;

    /**
     * the value getValue() will return when this instance's Input's value is at its minimum (or maximum),
     * as determined by Input::getMinimumValue() (or Input::getMaximumValue()), as specified by isInverted()
     */
    double minimum;

    /**
     * the value getValue() will return when this instance's Input's value is at its maximum (or minimum),
     * as determined by Input::getMaximumValue() (or Input::getMinimumValue()), as specified by isInverted()
     */
    double maximum;

    /**
     * the value getValue() will return when this instance's Input's value is at its neutral point,
     * as determined by Input::getNeutralValue()
     */
    double neutral;

    /** inverts the mapping between this output and its corresponding input about the neutral point */
    bool inverted;

    /**
     * causes this output to act as a toggle switch. A toggle output returns only either the #minimum
     * or #maximum value, and switches when its true value rises through #neutral.
     */
    bool toggle;

    /** the value to return when acting as a toggle switch */
    mutable double toggleValue;

    /** used to determine when to toggle, if enabled */
    mutable double lastValue;

};

}

#endif
