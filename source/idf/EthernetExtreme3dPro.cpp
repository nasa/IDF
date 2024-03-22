#include "idf/EthernetExtreme3dPro.hh"

namespace idf {

EthernetExtreme3dPro::EthernetExtreme3dPro() :
    EthernetWingMan("Extreme 3D Pro", 7) {}

void EthernetExtreme3dPro::decode(const std::vector<unsigned char>& data) {
    EthernetWingMan::decode(data);
    button8.setValue(data[4] >> 7 & 1);
    button9.setValue(data[6] & 1);
    button10.setValue(data[6] >> 1 & 1);
    button11.setValue(data[6] >> 2 & 1);
    button12.setValue(data[6] >> 3 & 1);
}

}
