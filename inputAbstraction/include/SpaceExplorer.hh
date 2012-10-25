/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/SpaceExplorer.cpp))
 */

#ifndef _SPACE_EXPLORER_HH_
#define _SPACE_EXPLORER_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a SpaceExplorer hand controller's input layout
 *
 * @author Derek Bankieris
 */
class SpaceExplorer {

    public:

    /** constructor */
    SpaceExplorer();

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** forward-backward translation */
    SingleInput forwardBackwardTranslation;

    /** left-right translation */
    SingleInput leftRightTranslation;

    /** up-down translation */
    SingleInput upDownTranslation;

    /** the button labeled 1 */
    SingleInput button1;

    /** the button labeled 2 */
    SingleInput button2;

    /** the button labeled - */
    SingleInput buttonMinus;

    /** the button labeled + */
    SingleInput buttonPlus;

    /** the button labeled ESC */
    SingleInput buttonEsc;

    /** the button labeled CTRL */
    SingleInput buttonCtrl;

    /** the button labeled ALT */
    SingleInput buttonAlt;

    /** the button labeled SHIFT */
    SingleInput buttonShift;

    /** the button labeled T */
    SingleInput buttonT;

    /** the button labeled L */
    SingleInput buttonL;

    /** the button labeled R */
    SingleInput buttonR;

    /** the button labeled 2D */
    SingleInput button2d;

    /** the button labeled F */
    SingleInput buttonF;

    /** the button labeled PANEL */
    SingleInput buttonPanel;

    /** the button labeled FIT */
    SingleInput buttonFit;

};

}

#endif
