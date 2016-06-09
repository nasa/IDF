#include "hardwareInterface/include/UsbChProPedals.hh"

namespace idf {

UsbChProPedals::UsbChProPedals(int vendorID, int productID) :
    UsbDevice("Ch Pro Pedals", vendorID, productID, 3) {}

void UsbChProPedals::decode(const std::vector<unsigned char>& data) {
    leftPedal.setValue(data[0]);
    rightPedal.setValue(data[1]);
    twist.setValue(data[2]);
}

}
