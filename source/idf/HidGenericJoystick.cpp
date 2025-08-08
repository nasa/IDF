#include "idf/HidGenericJoystick.hh"

namespace idf {

HidGenericJoystick::HidGenericJoystick() {}

void HidGenericJoystick::decode(const std::vector<unsigned char>& data) {
   printf("decode something from:");
   for (int d : data) {
      printf("%02X", d);
   }
   printf("\n");
}


} // namespace idf
