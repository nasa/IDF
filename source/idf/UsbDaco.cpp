#include "idf/UsbDaco.hh"

namespace idf {

UsbDaco::UsbDaco() :
   UsbDevice("Daco DF0201", 7) {}

void UsbDaco::decode(const std::vector<unsigned char>& data) {
   z.setValue(((unsigned)data[1] << 8) | data[0]);
   y.setValue(((unsigned)data[3] << 8) | data[2]);
   x.setValue(((unsigned)data[5] << 8) | data[4]);

   switch1.setValue(data[6] & 0x1);
}

} // namespace idf
