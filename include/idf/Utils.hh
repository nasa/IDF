/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Utils.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Utils.cpp}
 */

#ifndef IDF_UTILS_HH
#define IDF_UTILS_HH

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
