/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/MadCatz.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/MadCatz.cpp}
 */

#ifndef MAD_CATZ_HH
#define MAD_CATZ_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %MadCatz hand controller's input layout
 *
 * @author Derek Bankieris
 */
class MadCatz : public virtual InputLayout {

    public:

    /** constructor */
    MadCatz();

    /** destructor */
    virtual ~MadCatz() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** left throttle */
    SingleInput leftThrottle;

    /** right throttle */
    SingleInput rightThrottle;

    /** the trigger button (aka button 01) */
    SingleInput trigger;

    /** the button labeled 02 */
    SingleInput button2;

    /** the button labeled 03 */
    SingleInput button3;

    /** the button labeled 04 */
    SingleInput button4;

    /** the button labeled 05 */
    SingleInput button5;

    /** the button labeled 06 */
    SingleInput button6;

    /** the button labeled 07 */
    SingleInput button7;

    /** the button labeled 08 */
    SingleInput button8;

    /** the button labeled 09 */
    SingleInput button9;

    /** the button labeled 10 */
    SingleInput button10;

    /** the button labeled 11 */
    SingleInput button11;

    /** the button labeled X */
    SingleInput buttonX;

    /** the hat's northern trigger */
    SingleInput hatNorth;

    /** the hat's north-eastern trigger */
    SingleInput hatNorthEast;

    /** the hat's eastern trigger */
    SingleInput hatEast;

    /** the hat's south-eastern trigger */
    SingleInput hatSouthEast;

    /** the hat's southern trigger */
    SingleInput hatSouth;

    /** the hat's south-western trigger */
    SingleInput hatSouthWest;

    /** the hat's western trigger */
    SingleInput hatWest;

    /** the hat's north-western trigger */
    SingleInput hatNorthWest;

    /** the scroller Up */
    SingleInput scrollUp;

    /** the scroller Down */
    SingleInput scrollDown;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
