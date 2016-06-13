/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/WingMan.cpp}
 */

#ifndef _WING_MAN_HH_
#define _WING_MAN_HH_

#include "inputAbstraction/include/InputLayout.hh"
#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * %WingMan hand controller's input layout
 *
 * @author Derek Bankieris
 */
class WingMan : public virtual InputLayout {

    public:

    /** constructor */
    WingMan();

    /** destructor */
    virtual ~WingMan() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** the trigger button */
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

    /** the slider */
    SingleInput slider;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
