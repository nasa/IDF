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

   /**
    * @brief Construct a Generic Joystick derived from HID Report Descriptor
    * of the given device
    *
    * @param vendor HID Vendor ID to find the connected device
    * @param product HID product ID to find the connected device
    * @param interface specific interface of the connected device. HID
    * Scanner @link https://github.com/nasa/IDF/wiki/HID-Scanner can
    * help identify the correct interface
    */
   HidGenericJoystick(const int vendor, const int product, const int interface);

   void decode(const std::vector<unsigned char>& data);

   protected:

   /**
    * @brief Flag indicating whether the report descriptor contained a Z axis. If so
      use that for twist. Most joysticks will give the 'Rz' usage (0x35) for
      the twist axis. But some may have additional inputs and often this
      leads to using Z for twist. - This is NOT guaranteed, and may need to be
      manually overridden.
    */
   bool useZForTwist;

};

} // namespace idf

#endif
