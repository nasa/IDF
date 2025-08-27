#include "idf/UsbVirpilConstellationAlpha.hh"

namespace idf {

UsbVirpilConstellationAlpha::UsbVirpilConstellationAlpha() :
   UsbDevice("Virpil Constellation Alpha", 37) {}

void UsbVirpilConstellationAlpha::decode(const std::vector<unsigned char>& data) {
   VirpilMT50CM3::decode(data);
}

} // namespace idf
