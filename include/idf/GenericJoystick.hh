/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/GenericJoystick.cpp)

)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/GenericJoystick.cpp}
 */


#ifndef GENERIC_JOYSTICk_HH
#define GENERIC_JOYSTICk_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * @brief Generic joystick layout. Implementing device should guarantee at least:
 * Roll axis, Pitch axis and Trigger button. Other Inputs are not guaranteed
 *
 * @author Philip Kunz
 */
class GenericJoystick : public virtual InputLayout {

public:

   GenericJoystick();

   virtual ~GenericJoystick() {};

   // forward-backward pivoting
   SingleInput forwardBackwardPivot;

   // left-right pivoting
   SingleInput leftRightPivot;

   // twisting
   SingleInput twist;

   // the trigger button
   SingleInput trigger;

   // list of remaining buttons (if any)
   std::vector<SingleInput>buttons;

   // the slider
   SingleInput slider;

   // Hat Directions
   SingleInput HatNorth;
   SingleInput HatNorthEast;
   SingleInput HatEast;
   SingleInput HatSouthEast;
   SingleInput HatSouth;
   SingleInput HatSouthWest;
   SingleInput HatWest;
   SingleInput HatNorthWest;

protected:

   virtual const std::vector<Configurable>& getConfigurables();

};

} // namespace idf

#endif
