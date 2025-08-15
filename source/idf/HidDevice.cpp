#include "idf/HidDevice.hh"
#include "idf/IOException.hh"
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace idf {


HidDevice::HidDevice( int vendor, int product, int interface) :
   HidDevice(HidDevice::decodeDevice(vendor, product)) {
      addIdentification(Identification(vendor, product, interface));
   }


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

   return report;
}


void HidDevice::printHidDescriptor() {
   std::vector<unsigned char> report = getHidReportDescriptor();

   printf("\x1b[39;49m\nHID Report Descriptor (%lu bytes):\n   ", report.size());
   for(size_t i=0; i < report.size(); ++i) {
      printf("%02X ", report[i]);
      if (i % 16 == 15) printf("\n   ");
      else if (i % 8 == 7) printf(" ");
   }
}


void HidDevice::printDecodedHidInfo() {
   decoder.printDecodedInfo(decoded);
}

} //namespace idf
