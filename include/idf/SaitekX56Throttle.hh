/*
PURPOSE:
LIBRARY DEPENDENCIES: (
    (idf/SaitekX56Throttle.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SaitekX56Throttle.cpp}
 */

#ifndef SAITEK_X56_THROTTLE_HH
#define SAITEK_X56_THROTTLE_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * Saitek Pro Flight X-56 Rhino Throttle input layout
 * 
 * 
 * @author Philip Kunz
 */

class SaitekX56Throttle : public virtual InputLayout {

    public:

    /** constructor */
    SaitekX56Throttle();

    /** destructor */
    virtual ~SaitekX56Throttle() {};

    /** The thottle axis on left */
    SingleInput leftThrottle;

    /** The thottle axis on right */
    SingleInput rightThrottle;

    /** The button labeled "E" */
    SingleInput buttonE;

    /** The button labeled "F" */
    SingleInput buttonF;

    /** The button labeled "G" */
    SingleInput buttonG;

    /** The button labeled "H" */
    SingleInput buttonH;

    /** The button labeled "I" */
    SingleInput buttonI;

    /** The button by clicking in on the mini-joystick */
    SingleInput buttonJ;

    /** The button labeled "K", rocker with buttonL */
    SingleInput buttonK;

    /** The button labeled "L", rocker with buttonK */
    SingleInput buttonL;

    /** The North (up) Direction on the stick labeled "H3" */
    SingleInput hat3North;
    
    /** The North East (up + right) Direction on the stick labeled "H3" */
    SingleInput hat3NorthEast;

    /** The East (right) Direction on the stick labeled "H3" */
    SingleInput hat3East;

    /** The South East (down + right) Direction on the stick labeled "H3" */
    SingleInput hat3SouthEast;

    /** The South (down) Direction on the stick labeled "H3" */
    SingleInput hat3South;

    /** The South West (Down + left) Direction on the stick labeled "H3" */
    SingleInput hat3SouthWest;

    /** The West (left) Direction on the stick labeled "H3" */
    SingleInput hat3West;

    /** The North West (up + left) Direction on the stick labeled "H3" */
    SingleInput hat3NorthWest;

    /** The North (up) Direction on the stick labeled "H4" */
    SingleInput hat4North;
    
    /** The North East (up + right) Direction on the stick labeled "H4" */
    SingleInput hat4NorthEast;

    /** The East (right) Direction on the stick labeled "H4" */
    SingleInput hat4East;

    /** The South East (down + right) Direction on the stick labeled "H4" */
    SingleInput hat4SouthEast;

    /** The South (down) Direction on the stick labeled "H4" */
    SingleInput hat4South;

    /** The South West (Down + left) Direction on the stick labeled "H4" */
    SingleInput hat4SouthWest;

    /** The West (left) Direction on the stick labeled "H4" */
    SingleInput hat4West;

    /** The North West (up + left) Direction on the stick labeled "H4" */
    SingleInput hat4NorthWest;

    /** The 3 position switch labeled "MODE" */
    SingleInput mode;

    /** the Dial that is on top of Thottle2 */
    SingleInput rotary1;
    
    /** the Dial that is on bottom of Thottle2 */
    SingleInput rotary2;

    /** the Dial that is labeled "RTY3" */
    SingleInput rotary3;

    /** the Dial that is labeled "RTY4" */
    SingleInput rotary4;

    /** The Wheel (roll forward) on left side of leftThrottle */
    SingleInput scrollUp;

    /** The Wheel (roll back) on left side of leftThrottle */
    SingleInput scrollDown;

    /** the button labeled "SLD" */
    SingleInput slider;

    /** the button labeled "SW1" */
    SingleInput switch1;

    /** the button labeled "SW2" */
    SingleInput switch2;

    /** the button labeled "SW3" */
    SingleInput switch3;

    /** the button labeled "SW4" */
    SingleInput switch4;

    /** the button labeled "SW5" */
    SingleInput switch5;

    /** the button labeled "SW6" */
    SingleInput switch6;

    /** the button labeled "TGL1" */
    SingleInput toggle1;

    /** the button labeled "TGL2" */
    SingleInput toggle2;

    /** the button labeled "TGL3" */
    SingleInput toggle3;

    /** the button labeled "TGL4" */
    SingleInput toggle4;

    /** the small joystick on the rightThrottle */
    SingleInput miniStickForwardBackwardPivot;

    SingleInput miniStickUpDownPivot;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();
};

}


#endif