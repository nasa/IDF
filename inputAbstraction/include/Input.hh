/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/Input.cpp))
 */

#ifndef _INPUT_HH_
#define _INPUT_HH_

namespace idf {

/**
 * represents an input source from a device. An <code>Input</code>'s value is
 * one-dimensional and falls in the range
 * [<code>getMinimumValue()</code>, <code>getMaximumValue()</code>].
 *
 * @author Derek Bankieris
 */
class Input {

    public:

    /** destructor */
    virtual ~Input() {};

    /**
     * returns the minimum value this input can take
     *
     * @return the minimum possible value
     */
    virtual double getMinimumValue() const = 0;

    /**
     * returns the neutral value
     *
     * @return the neutral value
     */
    virtual double getNeutralValue() const = 0;

    /**
     * returns the maximum value this input can take
     *
     * @return the maximum possible value
     */
    virtual double getMaximumValue() const = 0;

    /**
     * returns the value
     *
     * @return the value
     */
    virtual double getValue() const = 0;

    /**
     * returns the value such that
     * <code>[getMinimumValue(), getNeutralValue(), getMaximumValue()]</code>
     * is normalized to <code>[-1, 0, 1]</code>
     *
     * @return the normalized value
     */
    virtual double getNormalizedValue() const;

};

}

#endif
