/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/CompositeInput.cpp))
 */

#ifndef _COMPOSITE_INPUT_HH_
#define _COMPOSITE_INPUT_HH_

#include <vector>

#include "inputAbstraction/include/Input.hh"

namespace idf {

/**
 * coalesces multiple <code>Input</code>s into a single entity, combining their
 * values as dictated by <code>simpleCombination</code>
 *
 * @author Derek Bankieris
 */
class CompositeInput : public Input {

    public:

    /**
     * <code>true</code>:
     * this instance's [minimum, neutral, maximum] values are set to
     * <code>[-1, 0, 1]</code>. Therefor, this output will take on its
     * minimum/neutral/maximum value when the weighted sum of the normalized
     * component inputs is at most/equal to/at least <code>-1/0/1</code>,
     * respectively.
     * <code>false</code>:
     * this instance's [minimum, neutral, maximum] values are set to
     * <code>[-n, 0, n]</code>, where <code>n</code> is the number of component
     * inputs. Therefor, this output will take on its minimum/neutral/maximum
     * value when the weighted sum of the normalized component inputs is equal
     * to <code>-1/0/1</code>, respectively.
     */
    bool simpleCombination;

    /**
     * constructor
     *
     * @param simpleCombination dictates the method by which inputs are combined
     */
    CompositeInput(bool simpleComination = true);

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
     * @return the combination, as dictated by <code>simpleCombination</code>,
     * of all added inputs
     */
    double getValue() const;

    /**
     * adds <code>input</code>, weighting its value by <code>weight</code> and
     * combining its value with all other added inputs. Adding an input that is
     * already contained by this instance has no effect.
     *
     * @param input the input to incorporate
     * @param weight the value by which to weight the input
     */
    void addInput(const Input& input, double weight = 1);

    /**
     * removes <code>input</code>, no longer combining its value with other
     * inputs. Removing an input that is not contained by this instance has no
     * effect.
     *
     * @param input the input to unincorporate
     */
    void removeInput(const Input& input);

    protected:

    /**
     * pairs an input with its weight
     */
    class Component {

        public:

        /** the input */
        const Input* input;

        /** the value by which to weight the input */
        double weight;

        /**
         * constructs an instance containing <code>input</code> weighted by
         * <code>weight</code>
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
