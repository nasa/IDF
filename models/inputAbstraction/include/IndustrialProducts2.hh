/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/IndustrialProducts2.cpp))
 */

#ifndef _INDUSTRIAL_PRODUCTS2_HH_
#define _INDUSTRIAL_PRODUCTS2_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents an IndustrialProducts2 hand controller's input layout
 *
 * @author Derek Bankieris
 */
class IndustrialProducts2 {

    public:

    /** constructor */
    IndustrialProducts2();

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** the trigger button */
    SingleInput trigger;

    /** the digital hat's northern trigger */
    SingleInput hatNorth;

    /** the digital hat's eastern trigger */
    SingleInput hatEast;

    /** the digital hat's southern trigger */
    SingleInput hatSouth;

    /** the digital hat's western trigger */
    SingleInput hatWest;

    /** the northwest button */
    SingleInput northWestButton;

    /** the southwest button */
    SingleInput southWestButton;

    /** the northeast button */
    SingleInput northEastButton;

    /** the southeast button */
    SingleInput southEastButton;

};

}

#endif
