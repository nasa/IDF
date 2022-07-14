/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SaitekX52.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SaitekX52.cpp}
 */

#ifndef SAITEK_X52_HH
#define SAITEK_X52_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Saitek Pro Flight X52 Flight System input layout
 *
 * @author Philip Kunz
 */
class SaitekX52 : public virtual InputLayout {

    public:

    /** constructor */
    SaitekX52();

    /** destructor */
    virtual ~SaitekX52() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    // /** twisting */
    SingleInput twist;

    /** trigger */
    SingleInput trigger;

    /** trigger */
    SingleInput triggerStage2;

    /** pinky trigger */
    SingleInput trigger2;

    /** buttons */
    SingleInput buttonFire;
    SingleInput buttonA;
    SingleInput buttonB;
    SingleInput buttonC;
    SingleInput buttonD;
    SingleInput buttonE;
    SingleInput buttonI;

    /** Stick Tobble Switches */
    SingleInput toggle1;
    SingleInput toggle2;
    SingleInput toggle3;
    SingleInput toggle4;
    SingleInput toggle5;
    SingleInput toggle6;


    /** hat1 directions */
    SingleInput hat1North;
    SingleInput hat1NorthEast;
    SingleInput hat1East;
    SingleInput hat1SouthEast;
    SingleInput hat1South;
    SingleInput hat1SouthWest;
    SingleInput hat1West;
    SingleInput hat1NorthWest;

    /** hat2 directions */
    SingleInput hat2North;
    SingleInput hat2NorthEast;
    SingleInput hat2East;
    SingleInput hat2SouthEast;
    SingleInput hat2South;
    SingleInput hat2SouthWest;
    SingleInput hat2West;
    SingleInput hat2NorthWest;

    /** hat3 directions */
    SingleInput hat3North;
    SingleInput hat3NorthEast;
    SingleInput hat3East;
    SingleInput hat3SouthEast;
    SingleInput hat3South;
    SingleInput hat3SouthWest;
    SingleInput hat3West;
    SingleInput hat3NorthWest;

    /** mode switch */
    SingleInput mode;

    /** throttle position */
    SingleInput throttle;

    /** scroll wheel up */
    SingleInput scrollUp;

    /** scroll wheel down */
    SingleInput scrollDown;

    /** rotary on front of throttle */
    SingleInput rotary1;

    /** rotary on top of throttle */
    SingleInput rotary2;

    /** mouse left button */
    SingleInput mouseLeftClick;

    /** mouse nub thingy */
    SingleInput thumbForwardBackwardPivot;
    SingleInput thumbUpDownPivot;

    /* slider on throttle */
    SingleInput slider;

    /* Display Buttons */
    SingleInput buttonFunction;
    SingleInput buttonStartStop;
    SingleInput buttonReset;


    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
