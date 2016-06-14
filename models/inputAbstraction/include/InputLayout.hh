/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(inputAbstraction/src/InputLayout.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/InputLayout.cpp}
 */

#ifndef _INPUT_LAYOUT_HH_
#define _INPUT_LAYOUT_HH_

#include "inputAbstraction/include/SingleInput.hh"
#include <string>
#include <vector>

namespace idf {

/**
 * base class for all input layouts
 *
 * @author Derek Bankieris
 */
class InputLayout {

    public:

    /** destructor */
    virtual ~InputLayout() {};

    protected:

    /** contains an Input for which configuration is meaningful */
    class Configurable {

        public:

        /** the configurable input */
        SingleInput* input;

        /** a human-readable description of the input */
        std::string name;

        /** the actual input variable name */
        std::string variable;

        /**
         * constructor
         *
         * @param input @copydoc input
         * @param name @copydoc name
         * @param variable @copydoc variable
         */
        Configurable(SingleInput& input, const std::string& name, const std::string& variable);

    };

    /**
     * gets the inputs for which configuration is meaningful
     *
     * @return inputs that support configuration
     */
    virtual const std::vector<Configurable>& getConfigurables();

    /**
     * appends @a data to @a destination
     *
     * @param data the data to be appended
     * @param destination the destination to which to append
     */
    template <class T>
    void append(const std::vector<T>& data, std::vector<T>& destination) {
        destination.insert(destination.end(), data.begin(), data.end());
    }

};

}

#endif
