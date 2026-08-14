/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMasterWarthogStickBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMasterWarthogStickBase.cpp}
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
 * @author Philip Kunz
 */
class ThrustMasterWarthogStickBase : public virtual InputLayout
{
public:
    /** constructor */
    ThrustMasterWarthogStickBase();

    /** destructor */
    virtual ~ThrustMasterWarthogStickBase() {}

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** hat north */
    SingleInput hatNorth;

    /** hat north east */
    SingleInput hatNorthEast;

    /** hat east */
    SingleInput hatEast;

    /** hat south east */
    SingleInput hatSouthEast;

    /** hat south */
    SingleInput hatSouth;

    /** hat south west */
    SingleInput hatSouthWest;

    /** hat west */
    SingleInput hatWest;

    /** hat north west */
    SingleInput hatNorthWest;

    /** trigger */
    SingleInput trigger;

    /** other buttons */
    SingleInput button2;
    SingleInput button3;
    SingleInput button4;
    SingleInput button5;
    SingleInput button6;
    SingleInput button7;
    SingleInput button8;
    SingleInput button9;
    SingleInput button10;
    SingleInput button11;
    SingleInput button12;
    SingleInput button13;
    SingleInput button14;
    SingleInput button15;
    SingleInput button16;
    SingleInput button17;
    SingleInput button18;
    SingleInput button19;

protected:
    virtual const std::vector<Configurable> & getConfigurables();
};

} // namespace idf

#endif
