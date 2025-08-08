/* PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/HidDevice.cpp)
)
*/

#ifndef IDF_HID_DEVICE_HH
#define IDF_HID_DEVICE_HH

#include "idf/UsbDevice.hh"
#include "idf/HidDecoder.hh"

namespace idf {

/**
 * @brief HidDevice is intended to help make IDF useful with generic
 * gaming devices that do not yet have a specific implementation.
 * ie joysticks, gamepads and "multi-axis" controllers
 * @author Philip Kunz
 * @date 2025-08-07
 */
class HidDevice : public UsbDevice {
   public:

   HidDevice();

   virtual ~HidDevice() {};

   virtual void open();

   protected:

   std::vector<HIDReport>hidReports;

   std::vector<unsigned char> hidReportDescriptor;

   virtual std::vector<unsigned char> getHidReportDescriptor();

   void parseHidReportDescriptor();
};

} // namespace idf

#endif
