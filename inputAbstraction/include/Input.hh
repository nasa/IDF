/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/Input.cpp))
 */

#ifndef _INPUT_HH_
#define _INPUT_HH_

#include <string>
#include <iostream>

namespace hardware {

/**
 * represents an input source from a device. An <code>Input</code>'s value is
 * one-dimensional and falls in the range
 * [<code>getMinimumValue()</code>, <code>getMaximumValue()</code>].
 *
 * @author Derek Bankieris
 */
class Input {

    public:

    /** destructs this instance */
    virtual ~Input() {};

    /**
     * returns the minimum value this input can take
     *
     * @return the minimum possible value
     */
    virtual double getMinimumValue() = 0;

    /**
     * returns the neutral value
     *
     * @return the neutral value
     */
    virtual double getNeutralValue() = 0;

    /**
     * returns the maximum value this input can take
     *
     * @return the maximum possible value
     */
    virtual double getMaximumValue() = 0;

    /**
     * returns the value
     *
     * @return the value
     */
    virtual double getValue() = 0;

    /**
     * returns the value such that
     * <code>[getMinimumValue(), getNeutralValue(), getMaximumValue()]</code>
     * is normalized to <code>[-1, 0, 1]</code>
     *
     * @return the normalized value
     */
    virtual double getNormalizedValue();

    virtual std::string toString();

};

}

#endif
