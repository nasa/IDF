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

   /**
    * @brief Find the specified device, read and decode its HID Report
    * Descriptor, then instantiate an HidDevice based on the decoded
    * descriptor information
    *
    * @param vendor HID Vendor ID to find the connected device
    * @param product HID product ID to find the connected device
    * @param interface specific interface of the connected device. HID
    * Scanner @link https://github.com/nasa/IDF/wiki/HID-Scanner can
    * help identify the correct interface
    */
   HidDevice(const int vendor, const int product, const int interface);

   /**
    * @brief Open device at @path, read and decode its HID Report
    * Descriptor, then instantiate an HidDevice based on the decoded
    * descriptor information
    *
    * @param devPath path to device
    */
   HidDevice(const std::string& devPath);

   HidDevice(const HidDescriptor* descriptor);

   virtual ~HidDevice() {};

   /**
    * @brief convenience method for displaying the Report Descriptor
    * in hex
    */
   void printHidDescriptor();

   /**
    * @brief convenience method for displaying the available reports and
    * inputs
    */
   void printDecodedHidInfo();

   /**
    * @brief open device with @a vendor and @a product, and parse the HID
    * report descriptor. This method exists mainly to ease instantiation
    *
    * @param vendor USB Vendor ID
    * @param product USB Product ID
    * @param interface HID interface # (use HidScanner to help find this info)
    * @return HidDescriptor struct enumerating the available reports
    */
   static HidDescriptor* decodeDevice(const int vendor, const int product, const int interface);

   /**
    * @brief open device at @a path, and parse the HID
    * report descriptor. This method exists mainly to ease instantiation
    *
    * @param path path to device
    * @return HidDescriptor struct enumerating the available reports
    */
   static HidDescriptor* decodeDevice(const std::string& targetPath);

protected:
   HidDecoder decoder;

   HidDescriptor descriptor;

   std::vector<unsigned char> hidReportDescriptor;

   virtual std::vector<unsigned char> getHidReportDescriptor();

private:
   static std::string resolvePath(const std::string& path);

};

} // namespace idf

#endif
