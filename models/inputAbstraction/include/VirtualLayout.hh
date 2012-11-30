/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/VirtualLayout.cpp))
 */

#ifndef _VIRTUAL_LAYOUT_HH_
#define _VIRTUAL_LAYOUT_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a six degree-of-freedom virtual input layout for use with the
 * Virtual Hand ContclockwiseCounterclockwiseRotationer application
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
