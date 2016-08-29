/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CompositeInput.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CompositeInput.cpp}
 */

#ifndef _COMPOSITE_INPUT_HH_
#define _COMPOSITE_INPUT_HH_

#include <vector>

#include "idf/Input.hh"

namespace idf {

/**
 * aggregates multiple {@link Input}s into a single entity, combining their
 * values as dictated by #simpleCombination
 *
 * @author Derek Bankieris
 */
class CompositeInput : public Input {

    public:

    /**
     * determines how constituent Input values are combined
     * - @c true<br>
     *   this instance's [minimum, neutral, maximum] values are set to
     *   <code>[-1, 0, 1]</code>. Therefore, this output will take on its
     *   minimum/neutral/maximum value when the weighted sum of the normalized
     *   component inputs is at most/equal to/at least @c -1/0/1, respectively.
     * - @c false<br>
     *   this instance's [minimum, neutral, maximum] values are set to
     *   <code>[-n, 0, n]</code>, where @c n is the number of component
     *   inputs. Therefore, this output will take on its minimum/neutral/maximum
     *   value when the weighted sum of the normalized component inputs is equal
     *   to @c -1/0/1, respectively.
     */
    bool simpleCombination;

    /**
     * constructor
     *
     * @param simpleCombination @copydoc simpleCombination
     */
    CompositeInput(bool simpleCombination = true);

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
     * gets the conglomerate value
     *
     * @return the combination, as dictated by #simpleCombination, of all added inputs
     */
    double getValue() const;

    /**
     * adds @a input, weighting its value by @a weight and combining its value with all other added inputs.
     * Adding an input that is already contained by this instance has no effect.
     *
     * @param input the input to incorporate
     * @param weight the value by which to weight the input
     */
    void addInput(const Input& input, double weight = 1);

    /**
     * removes @a input, no longer combining its value with other inputs.
     * Removing an input that is not contained by this instance has no effect.
     *
     * @param input the input to unincorporate
     */
    void removeInput(const Input& input);

    protected:

    /** pairs an input with its weight */
    class Component {

        public:

        /** the input */
        const Input* input;

        /** the value by which to weight the input */
        double weight;

        /**
         * constructs an instance containing @a input weighted by @a weight
         *
         * @param input the input
         * @param weight the value by which to weight the input
         */
        Component(const Input& input, double weight);

    };

    /** the constituent inputs */
    std::vector<const Component*> components;

};

}

#endif
