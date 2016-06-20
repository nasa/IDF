/** @trick_parse{everything} */

#ifndef _FEATURE_HH_
#define _FEATURE_HH_

#include <functional>

namespace idf {

/**
 * @author Derek Bankieris
 */
template <typename T, typename U>
class Feature {

    public:

    /** constructor */
    Feature(const std::function<T (const U&)>& function) :
        f(function) {}

    T getValue(const U& argument) const {
        return f(argument);
    }

    private:

    const std::function<T (const U&)> f;

};

}

#endif
