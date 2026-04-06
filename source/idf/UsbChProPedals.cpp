#include "idf/UsbChProPedals.hh"

namespace idf {

UsbChProPedals::UsbChProPedals() :
    UsbDevice("Ch Pro Pedals", 3) {}

void UsbChProPedals::decode(const std::vector<unsigned char>& data) {
    if (data.size() <= 2) { return; }
    leftPedal.setValue(data[0]);
    rightPedal.setValue(data[1]);
    twist.setValue(data[2]);
}

}
