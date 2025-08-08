/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/HidGenericJoystick.cpp)

)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/HidGenericJoystick.cpp}
 */


#ifndef HID_GENERIC_JOYSTICK_HH
#define HID_GENERIC_JOYSTICK_HH

#include "idf/HidDevice.hh"
#include "idf/GenericJoystick.hh"

namespace idf {

/**
 * @brief Generic class to open any HID device, read the HID Report Descriptor
 * and construct a usable controller with at least Roll axis, Pitch axis and
 * Trigger button. Attempts will also be made to map, but no guarantee is provided:
 * Throttle (Slider), Hat (8 directional) and a std::vector of buttons.
 *
 * @author Philip Kunz
 */
class HidGenericJoystick : public HidDevice, public virtual GenericJoystick {

   public:

   HidGenericJoystick();

   void decode(const std::vector<unsigned char>& data);

};

} // namespace idf

#endif