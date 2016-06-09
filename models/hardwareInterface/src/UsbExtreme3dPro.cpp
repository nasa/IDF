#include "hardwareInterface/include/UsbExtreme3dPro.hh"

namespace idf {

UsbExtreme3dPro::UsbExtreme3dPro(int vendorID, int productID) :
    UsbWingMan(vendorID, productID, "Extreme 3D Pro", 7) {}

void UsbExtreme3dPro::decode(const std::vector<unsigned char>& data) {
    UsbWingMan::decode(data);
    button8.setValue(data[4] >> 7 & 1);
    button9.setValue(data[6] & 1);
    button10.setValue(data[6] >> 1 & 1);
    button11.setValue(data[6] >> 2 & 1);
    button12.setValue(data[6] >> 3 & 1);
}

}
