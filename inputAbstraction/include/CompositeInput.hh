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
#include "Input.hh"

namespace idf {

/**
 * coalesces multiple {@link Input}s into a single entity, combining their
 * values as dictated by <code>proportional</code>
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
     * @param proportional wether inputs are combined proportionally (true)
     * or additively (false)
     */
    CompositeInput(bool simpleComination = true);

    /**
     * returns the minimum value this input can take
     *
     * @return the minimum possible value
     */
    virtual double getMinimumValue();

    /**
     * returns the neutral value
     *
     * @return the neutral value
     */
    virtual double getNeutralValue();

    /**
     * returns the maximum value this input can take
     *
     * @return the maximum possible value
     */
    virtual double getMaximumValue();

    /**
     * gets the conglomerate value
     *
     * @return the combination, as dictated by <code>proportional</code>, of
     * all added inputs
     */
    double getValue();

    /**
     * adds <code>input</code>, inverting its value as specified by
     * <code>invert</code> and combining its value with all other added
     * <code>Input</code>s
     *
     * @param input the <code>Input</code> to incorporate
     * @param invert weather or not to invert the input's value
     */
    void addInput(Input& input, double weight = 1);

    /**
     * removes <code>input</code>, no longer combining its value with other
     * <code>Input</code>s
     *
     * @param input the <code>Input</code> to unincorporate
     */
    void removeInput(Input& input);

    static void unitTest();

    private:

    class Component {

        public:
        Input *input;
        double weight;

        Component(Input& input, double weight);

    };

    /** the constituent inputs */
    std::vector<Component*> components;

};

}

#endif
