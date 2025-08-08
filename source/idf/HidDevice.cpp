#include "idf/HidDevice.hh"
#include "idf/IOException.hh"
#include <sstream>
#include <errno.h>
#include <string.h>
#include <iomanip>

namespace idf {

HidDevice::HidDevice( int vendor, int product) :
   HidDevice(HidDevice::decodeDevice(vendor, product)) {}

HidDevice::HidDevice(HidDecoded decoded_in) :
   UsbDevice("Generic " + decoded_in.type, decoded_in.maxReportLength),
   decoded(decoded_in) {}

HidDecoded HidDevice::decodeDevice(int vendor, int product) {

   std::ostringstream ss;
   hid_device* hidDevice;
   unsigned char buffer[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
   HidDecoder decoder;
   HidDecoded decDevice;

   if (!(hidDevice = hid_open(vendor, product, NULL))) {
      ss << "unable to open device " << vendor << ":" << product << " : ";
      ss << strerror(errno) << std::endl;
      throw IOException(ss.str());
   }

   int descSize = hid_get_report_descriptor(hidDevice, buffer, sizeof(buffer));

   if (descSize < 0) {
      ss << "unable to get HID report descriptor from " << vendor << ":" << product << " : ";
      ss << strerror(errno) << std::endl;
      hid_close(hidDevice);
      throw IOException(ss.str());
   }

   std::vector<unsigned char> descriptor(buffer, buffer + descSize);
   decDevice = decoder.parseDescriptor(descriptor);

   hid_close(hidDevice);
   return decDevice;
}

std::vector<unsigned char> HidDevice::getHidReportDescriptor() {
   unsigned char buffer[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
   int size = hid_get_report_descriptor(hidDevice, buffer, sizeof(buffer));

   if (size < 0) {
      perror("Unable to read HID Report Descriptor");
      return {};
   }

   std::vector<unsigned char> report(buffer, buffer + size);

   printf("\x1b[39;49m\nHID Report Descriptor (%d bytes):\n   ", size);
   for(int i=0; i < size; ++i) {
      printf("%02X ", buffer[i]);
      if (i % 16 == 15) printf("\n   ");
      else if (i % 8 == 7) printf(" ");
   }

   return report;
}

void HidDevice::printDecodedInfo() {
   std::ostringstream ss;
   ss << "Device Type:" << decoded.type << "\n";
   for (HidReport report : decoded.reports) {
      ss << "Report: " << report.id << "  (" << report.bytes_count << " bytes)\n";
      if (report.id != 0) {
            ss << "   Report ID       bits      0:7     value:      " << report.id << "\n";
         }
      for(HidInput input : report.inputs) {
         ss << "   " << std::setfill(' ') << std::setw(15) << std::left << input.name;
         if (input.start_bit == input.end_bit) {
            ss << " bit     " << std::setw(5) << std::right << input.start_bit << "     range:  ";
            ss << std::setw(5) << std::right << input.logical_min << ":";
            ss << std::left << input.logical_max << "\n";
         }
         else {
            ss << " bits  " << std::setw(5) << std::right << input.start_bit << ":";
            ss << std::setw(5) << std::left << input.end_bit;
            ss << " range:  ";
            ss << std::setw(5) << std::right << input.logical_min << ":";
            ss << std::setw(5) << std::left << input.logical_max << "   ";
            ss << std::setw(5) << std::right << input.physical_min << ":";
            ss << std::setw(5) << std::left << input.physical_max << "\n";
         }
      }
      ss << "\n";
   }
   printf(ss.str().c_str());
}

} //namespace idf
