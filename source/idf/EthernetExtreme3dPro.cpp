#include "idf/EthernetExtreme3dPro.hh"

namespace idf {

EthernetExtreme3dPro::EthernetExtreme3dPro(const std::string& host, unsigned short port ) :
    EthernetWingMan("Extreme 3D Pro", host, port, 14) {}

void EthernetExtreme3dPro::decode(const std::vector<unsigned char>& data) {
    EthernetWingMan::decode(data);
    button8.setValue( static_cast<double>(data[4] >> 7 & 1) );
    button9.setValue( static_cast<double>(data[6] & 1) );
    button10.setValue( static_cast<double>(data[6] >> 1 & 1) );
    button11.setValue( static_cast<double>(data[6] >> 2 & 1) );
    button12.setValue( static_cast<double>(data[6] >> 3 & 1) );
}

}
