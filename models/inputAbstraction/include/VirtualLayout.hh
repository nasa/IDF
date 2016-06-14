/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(inputAbstraction/src/VirtualLayout.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/VirtualLayout.cpp}
 */

#ifndef _VIRTUAL_LAYOUT_HH_
#define _VIRTUAL_LAYOUT_HH_

#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * six degree-of-freedom virtual input layout for use with the Virtual Hand %Controller application
 *
 * @author Derek Bankieris
 */
class VirtualLayout {

    public:

    /** constructor */
    VirtualLayout();

    /** leftRightRotation */
    SingleInput leftRightRotation;

    /** upDownRotation */
    SingleInput upDownRotation;

    /** clockwiseCounterclockwiseRotation */
    SingleInput clockwiseCounterclockwiseRotation;

    /** leftRightTranslation */
    SingleInput leftRightTranslation;

    /** upDownTranslation */
    SingleInput upDownTranslation;

    /** inOutTranslation */
    SingleInput inOutTranslation;

};

}

#endif
