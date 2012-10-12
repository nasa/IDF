/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/IndustrialProducts.cpp))
 */

#ifndef _INDUSTRIAL_PRODUCTS_HH_
#define _INDUSTRIAL_PRODUCTS_HH_

#include "hardwareInterface/include/InputDevice.hh"
#include "SingleInput.hh"

namespace hardware {

/**
 * represents an IndustrialProducts hand controller's input layout
 *
 * @author Derek Bankieris
 */
class IndustrialProducts {

    public:

    /** constructor */
    IndustrialProducts();

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** the trigger button */
    SingleInput trigger;

    /** the hat's northern trigger */
    SingleInput hatNorth;

    /** the hat's eastern trigger */
    SingleInput hatEast;

    /** the hat's southern trigger */
    SingleInput hatSouth;

    /** the hat's western trigger */
    SingleInput hatWest;

    /** the three-state switch */
    SingleInput threeStateSwitch;

    /** up-down pivoting of the hat */
    SingleInput hatUpDownPivot;

    /** left-right pivoting of the hat */
    SingleInput hatLeftRightPivot;

};

}

#endif
