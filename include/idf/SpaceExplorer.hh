/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SpaceExplorer.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SpaceExplorer.cpp}
 */

#ifndef SPACE_EXPLORER_HH
#define SPACE_EXPLORER_HH

#include "idf/SpaceBase.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %SpaceExplorer hand controller's input layout
 *
 * @author Derek Bankieris
 */
class SpaceExplorer : public virtual SpaceBase {

    public:

    /** constructor */
    SpaceExplorer();

    /** destructor */
    virtual ~SpaceExplorer() {};

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
