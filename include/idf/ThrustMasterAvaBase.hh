/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMasterAvaBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMasterAvaBase.cpp}
 */

#ifndef THRUSTMASTER_AVA_BASE_HH
#define THRUSTMASTER_AVA_BASE_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %ThrustMaster AVA Base hand controller's input layout. This device has
 * interchangeable grips, and not all grips have all inputs. e.g. While this
 * class lists Twist, F/B Thumbstick Pivot, L/R Thumbstick Pivot, and 32 buttons,
 * the compatible F-16 stick lacks Twist and the thumbstick Pivots, and has only
 * 18 buttons. Of those buttons, 12 are physically implemented as three
 * different 4-way hat switches. Thus, the standard IDF provided Controllers
 * (ie FlightController) will only have the most basic and essential inputs.
 *
 * @author Philip Kunz
 */
class ThrustMasterAvaBase : public virtual InputLayout {

    public:

    /** constructor */
    ThrustMasterAvaBase();

    /** destructor */
    virtual ~ThrustMasterAvaBase() {};

    /** forward-backward pivoting, uses HID X-axis (legacy HID consideration) */
    SingleInput forwardBackwardPivot;

    /** forward-backward pivoting, uses HID Y-axis (legacy HID consideration) */
    SingleInput leftRightPivot;

    /** twisting, uses HID Z-axis (legacy HID consideration) */
    SingleInput twist;

    /** input from Ry axis, likely a thumbstick */
    SingleInput forwardBackwardThumbstickPivot;

    /** input from Rx axis, likely a thumbstick */
    SingleInput leftRightThumbstickPivot;

    /** input from Rz axis. Sometimes throttle slider, analog brakes or a dial */
    SingleInput rotationZ;

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

    /** slider */
    SingleInput slider;

    /** dial */
    SingleInput dial;

    /** the trigger, or button1 */
    SingleInput trigger;

    /** button 2 */
    SingleInput button2;

    /** button 3 */
    SingleInput button3;

    /** button 4 */
    SingleInput button4;

    /** button 5 */
    SingleInput button5;

    /** button 6 */
    SingleInput button6;

    /** button 7 */
    SingleInput button7;

    /** button 8 */
    SingleInput button8;

    /** button 9 */
    SingleInput button9;

    /** button 10 */
    SingleInput button10;

    /** button 11 */
    SingleInput button11;

    /** button 12 */
    SingleInput button12;

    /** button 13 */
    SingleInput button13;

    /** button 14 */
    SingleInput button14;

    /** button 15 */
    SingleInput button15;

    /** button 16 */
    SingleInput button16;

    /** button 17 */
    SingleInput button17;

    /** button 18 */
    SingleInput button18;

    /** button 19 */
    SingleInput button19;

    /** button 20 */
    SingleInput button20;

    /** button 21 */
    SingleInput button21;

    /** button 22 */
    SingleInput button22;

    /** button 23 */
    SingleInput button23;

    /** button 24 */
    SingleInput button24;

    /** button 25 */
    SingleInput button25;

    /** button 26 */
    SingleInput button26;

    /** button 27 */
    SingleInput button27;

    /** button 28 */
    SingleInput button28;

    /** button 29 */
    SingleInput button29;

    /** button 30 */
    SingleInput button30;

    /** button 31 */
    SingleInput button31;

    /** button 32 */
    SingleInput button32;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

    private:

    ThrustMasterAvaBase& operator=(const ThrustMasterAvaBase&);

};

} // namespace idf

#endif