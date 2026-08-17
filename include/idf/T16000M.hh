/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/T16000M.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/T16000M.cpp}
 */

#ifndef THRUST_MASTER_T16000M_FCS_HH
#define THRUST_MASTER_T16000M_FCS_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * ThrustMaster T.16000M FCS joystick input layout https://www.thrustmaster.com/en-us/products/t-16000m-fcs/
 * This device has a switch on the button of the base that switches between "Right Handed" and "Left Handed"
 * modes. This toggles causes the 12 base buttons to mirror. The current mode is indicated in the read data
 * at data[2] >> 5, which is decoded into the "rightHandMode" input. It is not specified in the Report
 * Descriptor.
 *
 * The button defaults should be based on RightHanded mode because this is how the device ships.
 *
 * Right Handed <-->  Left Handed
 * button5      <-->  button11
 * button6      <-->  button12
 * button7      <-->  button13
 * button8      <-->  button14
 * button9      <-->  button15
 * button10     <-->  button16
 *
 * To help facilitate users that need consistent button behavior regardless of this mode switch,
 * a method
 * @author Philip Kunz
 */
class T16000M : public virtual InputLayout {

   public:

   /** constructor */
   T16000M();

   /** destructor */
   virtual ~T16000M() {};

   /** forward-backward pivoting */
   SingleInput forwardBackwardPivot;

   /** left-right pivoting */
   SingleInput leftRightPivot;

   /** twisting */
   SingleInput twist;

   /** the trigger */
   SingleInput trigger;

   /** middle button on top of stick */
   SingleInput middleButton;

   /** left button on top of stick */
   SingleInput leftButton;

   /** right button on top of stick */
   SingleInput rightButton;

   /** button on left side of base, front row, left */
   SingleInput button5;

   /** button on left side of base, front row, middle */
   SingleInput button6;

   /** button on left side of base, front row, right */
   SingleInput button7;

   /** button on left side of base, back row, right */
   SingleInput button8;

   /** button on left side of base, back row, middle */
   SingleInput button9;

   /** button on left side of base, back row, left */
   SingleInput button10;

   /** button on right side of base, front row, right */
   SingleInput button11;

   /** button on right side of base, front row, middle */
   SingleInput button12;

   /** button on right side of base, front row, left */
   SingleInput button13;

   /** button on right side of base, back row, left */
   SingleInput button14;

   /** button on right side of base, back row, middle */
   SingleInput button15;

   /** button on right side of base, back row, right */
   SingleInput button16;

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

   /** right-Handed Mode indicator */
   SingleInput rightHandMode;

   /** Enable/disable mode that all logical buttons are fixed to the right-handed layout */
   void setForceRightHandedMode(bool force);

   bool getForceRightHandedMode();

   protected:

   bool forceRightHanded = false;

   virtual const std::vector<Configurable>& getConfigurables();

   private:

   T16000M& operator=(const T16000M&);
};

} // namespace idf

#endif