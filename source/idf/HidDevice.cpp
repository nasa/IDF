#include "idf/HidDevice.hh"

namespace idf {

HidDevice::HidDevice() :
   UsbDevice("Generic HID Device", 64) {}

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

void HidDevice::open() {
   UsbDevice::open();
   hidReportDescriptor = getHidReportDescriptor();

   if (hidReportDescriptor.size() > 0) {
      parseHidReportDescriptor();
   }
}

} //namespace idf