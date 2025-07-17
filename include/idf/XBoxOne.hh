/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/XBoxOne.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/XBoxOne.cpp}
 */

#ifndef XBOX_ONE_HH
#define XBOX_ONE_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * Microsoft XBox One hand controller's input layout
 *
 * @author Stephen Montgomery-Smith
 */
class XBoxOne : public virtual InputLayout {

    public:

    /** constructor */
    XBoxOne();

    /** destructor */
    virtual ~XBoxOne() {};

    /** left analog stick left-right pivot */
    SingleInput leftAnalogLeftRightPivot;

    /** left analog stick up-down pivot */
    SingleInput leftAnalogUpDownPivot;

    /** left stick click in */
    SingleInput leftAnalogIn;

    /** left analog trigger */
    SingleInput leftAnalogTrigger;

    /** lower-right analog pad left-right pivot */
    SingleInput rightAnalogLeftRightPivot;

    /** lower-right analog pad up-down pivot */
    SingleInput rightAnalogUpDownPivot;

    /** right stick click in */
    SingleInput rightAnalogIn;

    /** right analog trigger */
    SingleInput rightAnalogTrigger;

    /** up on the directional pad */
    SingleInput directionalPadUp;

    /** down on the directional pad */
    SingleInput directionalPadDown;

    /** left on the directional pad */
    SingleInput directionalPadLeft;

    /** right on the directional pad */
    SingleInput directionalPadRight;

    /** the button labeled view */
    SingleInput viewButton;

    /** the center XBox button */
    SingleInput xBoxButton;

    /** the button labeled menu */
    SingleInput menuButton;

    /** the button labeled X */
    SingleInput xButton;

    /** the button labeled Y */
    SingleInput yButton;

    /** the button labeled A */
    SingleInput aButton;

    /** the button labeled B*/
    SingleInput bButton;

    /** the button labeled LB */
    SingleInput leftBumper;

    /** the button labeled RB*/
    SingleInput rightBumper;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
