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

   HidDevice( int vendor, int product );

   HidDevice( HidDecoded );

   virtual ~HidDevice() {};

   /**
    * @brief open device with @a vendor and @a product, and parse the HID
    * report descriptor.
    *
    * @param vendor USB Vendor ID
    * @param product USB Product ID
    * @return HIDDecodedDevice struct enumerating the available reports
    */
   static HidDecoded decodeDevice( int vendor, int product);

   void printDecodedInfo();

   protected:

   HidDecoded decoded;

   std::vector<HidReport>hidReports;

   std::vector<unsigned char> hidReportDescriptor;

   virtual std::vector<unsigned char> getHidReportDescriptor();

};

} // namespace idf

#endif
