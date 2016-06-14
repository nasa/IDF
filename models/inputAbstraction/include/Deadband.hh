/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(inputAbstraction/src/Deadband.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/Deadband.cpp}
 */

#ifndef _DEADBAND_HH_
#define _DEADBAND_HH_

namespace idf {

/**
 * a filter that returns the specified output value when an input value falls within its bounds, exclusive
 *
 * @author Derek Bankieris
 */
class Deadband {

    public:

    /**
     * constructs an instance with a deadband value of <code>(lowerBound + upperBound) / 2</code>
     *
     * @param lowerBound the lower value
     * @param upperBound the upper value
     */
    Deadband(double lowerBound, double upperBound);

    /**
     * constructor
     *
     * @param lowerBound the lower value
     * @param upperBound the upper value
     * @param value the deadband value
     */
    Deadband(double lowerBound, double upperBound, double value);

    /**
     * sets the range over which this deadband will filter. The deadband value
     * will be <code>(lowerBound + upperBound) / 2</code>.
     *
     * @param lowerBound the lower value
     * @param upperBound the upper value
     */
    void setRange(double lowerBound, double upperBound);

    /**
     * sets the range over which this deadband will filter and the value to be returned
     *
     * @param lowerBound the lower value
     * @param upperBound the upper value
     * @param value the deadband value
     */
    void setRange(double lowerBound, double upperBound, double value);

    /**
     * returns the lower bound
     *
     * @return the lower bound
     */
    double getLowerBound() const;

    /**
     * returns the upper bound
     *
     * @return the upper bound
     */
    double getUpperBound() const;

    /**
     * returns the deadband value
     *
     * @return the deadband value
     */
    double getDeadbandValue() const;

    /**
     * filters @a value, returning the deadband value if @a value falls within this
     * deadband's range, and @a value, unchanged, otherwise
     *
     * @param value the value to filter
     *
     * @return the filtered value
     */
    double filter(double value) const;

    /** performs a shallow comparison of all member values */
    bool operator==(const Deadband& other) const;

    protected:

    /** the lower bound */
    double lowerBound;

    /** the upper bound */
    double upperBound;

    /** the value of this deadband */
    double value;

};

}

#endif
