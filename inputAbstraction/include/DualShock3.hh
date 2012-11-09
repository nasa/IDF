/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/DualShock3.cpp))
 */

#ifndef _DUAL_SHOCK_3_HH_
#define _DUAL_SHOCK_3_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a Sony DUALSHOCK3 SIXAXIS hand controller's input layout
 *
 * @author Derek Bankieris
 */
class DualShock3 {

    public:

    /** constructor */
    DualShock3();

    /** left analog pad left-right pivot */
    SingleInput leftAnalogLeftRightPivot;

    /** left analog pad up-down pivot */
    SingleInput leftAnalogUpDownPivot;

    /** pushing in of the left analog pad */
    SingleInput leftAnalogIn;

    /** right analog pad left-right pivot */
    SingleInput rightAnalogLeftRightPivot;

    /** right analog pad up-down pivot */
    SingleInput rightAnalogUpDownPivot;

    /** pushing in of the right analog pad */
    SingleInput rightAnalogIn;

    /** up on the directional pad */
    SingleInput directionalPadUp;

    /** down on the directional pad */
    SingleInput directionalPadDown;

    /** left on the directional pad */
    SingleInput directionalPadLeft;

    /** right on the directional pad */
    SingleInput directionalPadRight;

    /** the button labeled select */
    SingleInput selectButton;

    /** the center PlayStation button */
    SingleInput playStationButton;

    /** the button labeled start */
    SingleInput startButton;

    /** the button labeled with a sqaure */
    SingleInput squareButton;

    /** the button labeled with a triangle */
    SingleInput triangleButton;

    /** the button labeled with an X */
    SingleInput xButton;

    /** the button labeled with a circle */
    SingleInput circleButton;

    /** the button labeled 1 above the side labeled L */
    SingleInput leftBumper;

    /** the button labeled 1 above the side labeled R*/
    SingleInput rightBumper;

    /** the button labeled 2 above the side labeled L */
    SingleInput leftTrigger;

    /** the button labeled 2 above the side labeled R */
    SingleInput rightTrigger;

};

}

#endif
