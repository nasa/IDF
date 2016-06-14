/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(inputAbstraction/src/Utils.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/Utils.cpp}
 */

#ifndef _IDF_UTILS_HH_
#define _IDF_UTILS_HH_

namespace idf {

/**
 * bounds @a value to [-1, 1]
 *
 * @param value the value to bound
 *
 * @return the bounded value
 */
double bound(double value);

}

#endif
