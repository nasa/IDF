/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SpaceMouse.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SpaceMouse.cpp}
 */

#ifndef SPACE_MOUSE_HH
#define SPACE_MOUSE_HH

#include "idf/SpaceBase.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %SpaceMouse hand controller's input layout
 *
 * @author Derek Bankieris
 */
class SpaceMouse : public virtual SpaceBase {

    public:

    /** constructor */
    SpaceMouse();

    /** destructor */
    virtual ~SpaceMouse() {};

    /** the button labeled 1 */
    SingleInput button1;

    /** the button labeled 2 */
    SingleInput button2;

    /** the button labeled 3 */
    SingleInput button3;

    /** the button labeled 4 */
    SingleInput button4;

    /** the button labeled ESC */
    SingleInput buttonEsc;

    /** the button labeled CTRL */
    SingleInput buttonCtrl;

    /** the button labeled ALT */
    SingleInput buttonAlt;

    /** the button labeled SHIFT */
    SingleInput buttonShift;

    /** the button labeled with a square and arrow */
    SingleInput buttonFlatRotation;

    /** the button labeled T */
    SingleInput buttonT;

    /** the button labeled R */
    SingleInput buttonR;

    /** the button labeled F */
    SingleInput buttonF;

    /** the button depicting the center mouse being twisted */
    SingleInput buttonMouseRotation;

    /** the button labeled MENU */
    SingleInput buttonMenu;

    /** the button labeled FIT */
    SingleInput buttonFit;

};

}

#endif
