#include "idf/UsbDacoThc.hh"

namespace idf {

UsbDacoThc::UsbDacoThc() :
   UsbDevice("Daco THC DF0201", 7) {}

void UsbDacoThc::decode(const std::vector<unsigned char>& data) {
   leftRightTranslation.setValue(((unsigned)data[1] << 8) | data[0]);
   upDownTranslation.setValue(((unsigned)data[3] << 8) | data[2]);
   forwardBackwardTranslation.setValue(((unsigned)data[5] << 8) | data[4]);

   switch1.setValue(data[6] & 0x1);
}

} // namespace idf
