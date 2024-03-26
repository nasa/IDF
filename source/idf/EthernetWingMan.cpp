#include "idf/EthernetWingMan.hh"

namespace idf {

EthernetWingMan::EthernetWingMan() :
    EthernetDevice("Wing Man", 6) {}

EthernetWingMan::EthernetWingMan(const std::string& id, unsigned length) :
    EthernetDevice(id, length) {}

void EthernetWingMan::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((unsigned)data[1] & 3) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[2] & 0xF) << 6 | data[1] >> 2);
    twist.setValue(data[3]);

    trigger.setValue(data[4] & 1);
    button2.setValue(data[4] >> 1 & 1);
    button3.setValue(data[4] >> 2 & 1);
    button4.setValue(data[4] >> 3 & 1);
    button5.setValue(data[4] >> 4 & 1);
    button6.setValue(data[4] >> 5 & 1);
    button7.setValue(data[4] >> 6 & 1);

    unsigned int hat = data[2] >> 4;

    hatNorth.setValue(hat == 0);
    hatNorthEast.setValue(hat == 1);
    hatEast.setValue(hat == 2);
    hatSouthEast.setValue(hat == 3);
    hatSouth.setValue(hat == 4);
    hatSouthWest.setValue(hat == 5);
    hatWest.setValue(hat == 6);
    hatNorthWest.setValue(hat == 7);

    slider.setValue(data[5]);
}

}
