#include "idf/EthernetWingMan.hh"

namespace idf {

EthernetWingMan::EthernetWingMan(const std::string& host, unsigned short port ) :
    EthernetDevice("Wing Man", host, port, 6) {}

EthernetWingMan::EthernetWingMan(const std::string& id, const std::string& host, unsigned short port, unsigned length) :
    EthernetDevice(id, host, port, length) {}

void EthernetWingMan::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue( static_cast<double>(((unsigned)data[1] & 3) << 8 | data[0]) );
    forwardBackwardPivot.setValue( static_cast<double>(((unsigned)data[2] & 0xF) << 6 | data[1] >> 2) );
    twist.setValue( static_cast<double>(data[3]) );

    trigger.setValue( static_cast<double>(data[4] & 1) );
    button2.setValue( static_cast<double>(data[4] >> 1 & 1) );
    button3.setValue( static_cast<double>(data[4] >> 2 & 1) );
    button4.setValue( static_cast<double>(data[4] >> 3 & 1) );
    button5.setValue( static_cast<double>(data[4] >> 4 & 1) );
    button6.setValue( static_cast<double>(data[4] >> 5 & 1) );
    button7.setValue( static_cast<double>(data[4] >> 6 & 1) );

    unsigned int hat = data[2] >> 4;

    hatNorth.setValue( static_cast<double>(hat == 0) );
    hatNorthEast.setValue( static_cast<double>(hat == 1) );
    hatEast.setValue( static_cast<double>(hat == 2) );
    hatSouthEast.setValue( static_cast<double>(hat == 3) );
    hatSouth.setValue( static_cast<double>(hat == 4) );
    hatSouthWest.setValue( static_cast<double>(hat == 5) );
    hatWest.setValue( static_cast<double>(hat == 6) );
    hatNorthWest.setValue( static_cast<double>(hat == 7) );

    slider.setValue( static_cast<double>(data[5]) );
}

}
