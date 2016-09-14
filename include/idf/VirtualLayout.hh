/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/VirtualLayout.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/VirtualLayout.cpp}
 */

#ifndef VIRTUAL_LAYOUT_HH
#define VIRTUAL_LAYOUT_HH

#include "idf/SingleInput.hh"

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
