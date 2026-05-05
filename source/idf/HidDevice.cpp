#include "idf/HidDevice.hh"
#include "idf/IOException.hh"
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace idf {

HidDevice::HidDevice(const int vendor, const int product, const int interface) :
   HidDevice(HidDevice::decodeDevice(vendor, product, interface))
   {}

HidDevice::HidDevice(const std::string& devPath) :
   HidDevice(HidDevice::decodeDevice(devPath))
   {
      setPath(devPath);
   }

HidDevice::HidDevice(const HidDescriptor* descriptor_in) :
   UsbDevice("Generic " + descriptor_in->type, descriptor_in->maxReportLength),
   descriptor(*descriptor_in)
   {
      std::wcout << "Added device to IDF: " << descriptor.vendor_string << " " << descriptor.product_string
         << " (" << std::hex << descriptor.vendor << ":" << descriptor.product
         << ":" << std::dec << descriptor.interface << ")" << std::endl;
      addIdentification(Identification(descriptor.vendor, descriptor.product, descriptor.interface));
   }

HidDescriptor* HidDevice::decodeDevice(const int vendor, const int product, const int interface)
{
   std::ostringstream ss;
   hid_device* hidDevice;
   unsigned char buffer[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
   HidDecoder decoder;

   if (!(hidDevice = hid_open(vendor, product, NULL))) {
      ss << "unable to open device " << std::hex << vendor << ":" << product << " : ";
      ss << strerror(errno) << std::endl;
      throw IOException(ss.str());
   }

   int descSize = hid_get_report_descriptor(hidDevice, buffer, sizeof(buffer));

   if (descSize < 0) {
      ss << "unable to get HID report descriptor from " << std::hex << std::setw(4) << std::setfill('0') << vendor << ":" << product << " : ";
      ss << strerror(errno) << std::endl;
      hid_close(hidDevice);
      throw IOException(ss.str());
   }

   wchar_t vendStr[255];
   wchar_t prodStr[255];
   if (hid_get_manufacturer_string(hidDevice, vendStr, 255) != 0) {
      ss << "unable to read manufacturer string from device: " << strerror(errno) << hid_error(hidDevice) << std::endl;
      throw IOException(ss.str());
   }

   if (hid_get_product_string(hidDevice, prodStr, 255) != 0) {
      ss << "unable to read manufacturer string from device: " << strerror(errno) << hid_error(hidDevice) << std::endl;
      throw IOException(ss.str());
   }

   std::wcout << "device = " << vendStr << " " << prodStr << std::endl;

   std::vector<unsigned char> descriptor(buffer, buffer + descSize);
   HidDescriptor* decDevice = decoder.parseDescriptor(descriptor);
   decDevice->vendor = vendor;
   decDevice->product = product;
   decDevice->interface = interface;
   decDevice->vendor_string = vendStr;
   decDevice->product_string = prodStr;

   hid_close(hidDevice);
   return decDevice;
}

HidDescriptor* HidDevice::decodeDevice(const std::string& targetPath)
{
   hid_device* hidDevice;
   unsigned char buffer[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
   HidDecoder decoder;

   std::string resolvedPath = resolvePath(targetPath);
   std::ostringstream ss;
   ss << "Failed to open HID device at " << targetPath;
   if (resolvedPath != targetPath) {
      ss << " (which resolves to " << resolvedPath << ")";
   }
   ss << ": ";

   struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
   for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {

      // if the path matches
      if (!strcmp(resolvedPath.c_str(), deviceInfo->path)) {
         std::cout << "resolved device at " << resolvedPath << " is a ";
         std::wcout << deviceInfo->manufacturer_string << " "
            << deviceInfo->product_string << " ";

         std::cout << std::hex << std::setw(4) << std::setfill('0') << deviceInfo->vendor_id << ":" << deviceInfo->product_id
            << std::endl;

         // TODO: check that the device isn't already open

         // Open device to read Report Descriptor
         if (!(hidDevice = hid_open_path(resolvedPath.c_str()))) {
            ss << strerror(errno) << ". See the https://github.com/nasa/IDF/wiki for troubleshooting.";
            throw IOException(ss.str());
         }

         // decode the RD
         int descSize = hid_get_report_descriptor(hidDevice, buffer, sizeof(buffer));

         if (descSize < 0) {
            ss << "unable to get HID report descriptor from "
               << targetPath << strerror(errno) << std::endl;
            hid_close(hidDevice);
            throw IOException(ss.str());
         }

         wchar_t vendStr[255];
         wchar_t prodStr[255];
         if (hid_get_manufacturer_string(hidDevice, vendStr, 255) != 0) {
            ss << "unable to read manufacturer string from device: " << strerror(errno) << hid_error(hidDevice) << std::endl;
            throw IOException(ss.str());
         }

         if (hid_get_product_string(hidDevice, prodStr, 255) != 0) {
            ss << "unable to read manufacturer string from device: " << strerror(errno) << hid_error(hidDevice) << std::endl;
            throw IOException(ss.str());
         }

         std::vector<unsigned char> descriptor(buffer, buffer + descSize);
         HidDescriptor* decDevice = decoder.parseDescriptor(descriptor);
         decDevice->vendor = deviceInfo->vendor_id;
         decDevice->product = deviceInfo->product_id;
         decDevice->interface = deviceInfo->interface_number;
         decDevice->vendor_string = vendStr;
         decDevice->product_string = prodStr;

         // release the enumeration
         hid_free_enumeration(enumerationHead);

         hid_close(hidDevice);
         return decDevice;
      }
   }

   // path not found
   hid_free_enumeration(enumerationHead);
   ss << "There is no device at this path.";
   throw IOException(ss.str());
}

std::vector<unsigned char> HidDevice::getHidReportDescriptor()
{
   unsigned char buffer[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
   int size = hid_get_report_descriptor(hidDevice, buffer, sizeof(buffer));

   if (size < 0) {
      perror("Unable to read HID Report Descriptor");
      return {};
   }

   std::vector<unsigned char> report(buffer, buffer + size);

   return report;
}

void HidDevice::printHidDescriptor()
{
   std::vector<unsigned char> report = getHidReportDescriptor();

   printf("\nHID Report Descriptor (%lu bytes):\n   ", report.size());
   for(size_t i=0; i < report.size(); ++i) {
      printf("%02X ", report[i]);
      if (i % 16 == 15) printf("\n   ");
      else if (i % 8 == 7) printf(" ");
   }
}

void HidDevice::printDecodedHidInfo()
{
   decoder.printDecodedInfo(descriptor);
}

std::string HidDevice::resolvePath(const std::string& unresolvedPath)
{
    #ifdef __APPLE__
        return unresolvedPath;
    #else
        char resolvedPath[PATH_MAX];
        if (!realpath(unresolvedPath.c_str(), resolvedPath)) {
            throw IOException("Failed to resolve " + unresolvedPath + ": " + strerror(errno));
        }
        return resolvedPath;
    #endif
}

} //namespace idf
