/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/WarthogStickBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/WarthogStickBase.cpp}
 */

#ifndef THRUSTMASTER_WARTHOG_STICK_HH
#define THRUSTMASTER_WARTHOG_STICK_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf
{

/**
 * @brief Base layout of the ThrustMaster HOTAS WARTHOG Joystick
 *
 * This device has a modular grip that can be replaced. Thus, the available inputs
 * are mostly just discrete buttons. It is intended to be used with their
 * proprietary T.A.R.G.E.T. software (Windows) to create custom virtual
 * mappings.
 *
 * Thus, this base definition will only list the buttons. Each grip needs its
 * own layout
 *
 * Manual with button numbers for included VIPER grip:
 * https://ts.thrustmaster.com/download/accessories/pc/hotas/manual/HOTAS_Warthog/HOTAS_Warthog_Manual.pdf
 * @author Philip Kunz
 */
class WarthogStickBase : public virtual InputLayout
{
public:
    /** constructor */
    WarthogStickBase();

    /** destructor */
    virtual ~WarthogStickBase() {}

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** hat north (Trim Switch, grey hat, top left of face) */
    SingleInput hatNorth;

    /** hat north east (Trim Switch, grey hat, top left of face) */
    SingleInput hatNorthEast;

    /** hat east (Trim Switch, grey hat, top left of face) */
    SingleInput hatEast;

    /** hat south east (Trim Switch, grey hat, top left of face) */
    SingleInput hatSouthEast;

    /** hat south (Trim Switch, grey hat, top left of face) */
    SingleInput hatSouth;

    /** hat south west (Trim Switch, grey hat, top left of face) */
    SingleInput hatSouthWest;

    /** hat west (Trim Switch, grey hat, top left of face) */
    SingleInput hatWest;

    /** hat north west (Trim Switch, grey hat, top left of face) */
    SingleInput hatNorthWest;

    /** trigger */
    SingleInput trigger;

    /** Weapon Release Button (Red, top left of face) */
    SingleInput button2WeaponRelease;

    /** Nose Wheel Steering (pinkie, opposite side, bottom of grip) */
    SingleInput button3NoseSteering;

    /** Paddle */
    SingleInput button4Paddle;

    /** Master Mode button (grey, right side, foreward of face) */
    SingleInput button5MasterMode;

    /** Trigger 2nd stage */
    SingleInput button6Trigger2nd;

    /** Button 7: Target Management System Up (Black ridged 4-way hat below Weapon Realease / button 2) */
    SingleInput button7TmsUp;

    /** Button 8: Target Management System Right (Black ridged 4-way hat below Weapon Realease / button 2) */
    SingleInput button8TmsRight;

    /** Button 9: Target Management System Down (Black ridged 4-way hat below Weapon Realease / button 2) */
    SingleInput button9TmsDown;

    /** Button 10: Target Management System Left (Black ridged 4-way hat below Weapon Realease / button 2) */
    SingleInput button10TmsLeft;

    /** Button 11: Data Management System Up (Black D-pad style 4-way hat, below the Grey 8 way hat) */
    SingleInput button11DmsUp;

    /** Button 12: Data Management System Right (Black D-pad style 4-way hat, below the Grey 8 way hat) */
    SingleInput button12DmsRight;

    /** Button 13: Data Management System Down (Black D-pad style 4-way hat, below the Grey 8 way hat) */
    SingleInput button13DmsDown;

    /** Button 14: Data Management System Up (Black D-pad style 4-way hat, below the Grey 8 way hat) */
    SingleInput button14DmsLeft;

    /** Button 15: Coutermeasure System Fwd (Thumbstick style 4-way hat) */
    SingleInput button15CmsForward;

    /** Button 16: Coutermeasure System Right (Thumbstick style 4-way hat) */
    SingleInput button16CmsRight;

    /** Button 17: Coutermeasure System Back (Thumbstick style 4-way hat) */
    SingleInput button17CmsBack;

    /** Button 18: Coutermeasure System Left (Thumbstick style 4-way hat) */
    SingleInput button18CmsLeft;

    /** Button 19: Coutermeasure System Push (Thumbstick style 4-way hat) */
    SingleInput button19CmsPush;

protected:
    virtual const std::vector<Configurable> & getConfigurables();
};

} // namespace idf

#endif
