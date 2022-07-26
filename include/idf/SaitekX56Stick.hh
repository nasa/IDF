/*
PURPOSE:
LIBRARY DEPENDENCIES: (
    (idf/SaitekX56Stick.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SaitekX56Stick.cpp}
 */

#ifndef SAITEK_X56_STICK_HH
#define SAITEK_X56_STICK_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * Saitek Pro Flight X-56 Rhino Throttle input layout
 * 
 * 
 * @author Philip Kunz
 */

class SaitekX56Stick : public virtual InputLayout {

    public:

    /** constructor */
    SaitekX56Stick();

    /** destructor */
    virtual ~SaitekX56Stick() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** thumb stick forward-backward pivoting */
    SingleInput thumbForwardBackwardPivot;

    /** thumb stick left-right pivoting*/
    SingleInput thumbLeftRightPivot;

    /** the primary trigger */
    SingleInput trigger1;

    /** the picky trigger */
    SingleInput trigger2;

    /** The button labeled "A" */
    SingleInput buttonA;

    /** The button labeled "B" */
    SingleInput buttonB;

    /** The button labeled "C" */
    SingleInput buttonC;

    /** The button labeled "D" */
    SingleInput buttonD;

    /** Up/Down pivot on H1 regardless of left/right */
    SingleInput hat1UpDownPivot;

    /** Left/Right pivot on H1 redardless of up/down */
    SingleInput hat1LeftRightPivot;

    /** The North (up) Direction on the hat labeled "H1" */
    SingleInput hat1North;
    
    /** The North East (up + right) Direction on the hat labeled "H1" */
    SingleInput hat1NorthEast;

    /** The East (right) Direction on the hat labeled "H1" */
    SingleInput hat1East;

    /** The South East (down + right) Direction on the hat labeled "H1" */
    SingleInput hat1SouthEast;

    /** The South (down) Direction on the hat labeled "H1" */
    SingleInput hat1South;

    /** The South West (Down + left) Direction on the hat labeled "H1" */
    SingleInput hat1SouthWest;

    /** The West (left) Direction on the hat labeled "H1" */
    SingleInput hat1West;

    /** The North West (up + left) Direction on the hat labeled "H1" */
    SingleInput hat1NorthWest;

    /** Up/Down pivot on H2 regardless of left/right */
    SingleInput hat2UpDownPivot;

    /** Left/Right pivot on H2 redardless of up/down */
    SingleInput hat2LeftRightPivot;

    /** The North (up) Direction on the hat labeled "H2" */
    SingleInput hat2North;
    
    /** The North East (up + right) Direction on the hat labeled "H2" */
    SingleInput hat2NorthEast;

    /** The East (right) Direction on the hat labeled "H2" */
    SingleInput hat2East;

    /** The South East (down + right) Direction on the hat labeled "H2" */
    SingleInput hat2SouthEast;

    /** The South (down) Direction on the hat labeled "H2" */
    SingleInput hat2South;

    /** The South West (Down + left) Direction on the hat labeled "H2" */
    SingleInput hat2SouthWest;

    /** The West (left) Direction on the hat labeled "H2" */
    SingleInput hat2West;

    /** The North West (up + left) Direction on the hat labeled "H2" */
    SingleInput hat2NorthWest;


    /** Up/Down pivot on POV regardless of left/right */
    SingleInput povUpDownPivot;

    /** Left/Right pivot on POV redardless of up/down */
    SingleInput povLeftRightPivot;

    /** The North (up) Direction on the hat labeled "POV" */
    SingleInput povNorth;
    
    /** The North East (up + right) Direction on the hat labeled "POV" */
    SingleInput povNorthEast;

    /** The East (right) Direction on the hat labeled "POV" */
    SingleInput povEast;

    /** The South East (down + right) Direction on the hat labeled "POV" */
    SingleInput povSouthEast;

    /** The South (down) Direction on the hat labeled "POV" */
    SingleInput povSouth;

    /** The South West (Down + left) Direction on the hat labeled "POV" */
    SingleInput povSouthWest;

    /** The West (left) Direction on the hat labeled "POV" */
    SingleInput povWest;

    /** The North West (up + left) Direction on the hat labeled "POV" */
    SingleInput povNorthWest;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();
};

}


#endif