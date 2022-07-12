#include "idf/UsbSaitekX52.hh"

namespace idf {

UsbSaitekX52::UsbSaitekX52() :
    UsbDevice("Saitek Pro Flight X52 Flight System", 14) {}


UsbSaitekX52::UsbSaitekX52(const std::string& id, unsigned length) :
    UsbDevice(id, length) {}

void UsbSaitekX52::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue( ((unsigned)data[1] & 0x7) << 8 | data[0]);
    forwardBackwardPivot.setValue( ((unsigned)data[2] & 0x3F) << 5 | data[1] >> 3);
    twist.setValue( ((unsigned)data[3] << 2) | (data[2] & 0xC0 >> 6) );
    throttle.setValue( data[4]);
    rotary1.setValue( data[5]);
    rotary2.setValue( data[6]);
    slider.setValue( data[7]);
    trigger.setValue( data[8] & 0x1);
    buttonFire.setValue( data[8] >> 1 & 0x1);
    buttonA.setValue( data[8] >> 2 & 0x1);
    buttonB.setValue( data[8] >> 3 & 0x1);
    buttonC.setValue( data[8] >> 4 & 0x1);
    trigger2.setValue( data[8] >> 5 & 0x1);
    buttonD.setValue( data[8] >> 6 & 0x1);
    buttonE.setValue( data[8] >> 7 & 0x1);
    toggle1.setValue( data[9] & 0x1);
    toggle2.setValue( data[9] >> 1 & 0x1);
    toggle3.setValue( data[9] >> 2 & 0x1);
    toggle4.setValue( data[9] >> 3 & 0x1);
    toggle5.setValue( data[9] >> 4 & 0x1);
    toggle6.setValue( data[9] >> 5 & 0x1);
    triggerStage2.setValue( data[9] >> 6 & 0x1);

    char hat1 = (data[9] >> 7 & 0x1) | (data[10] << 1 & 0xE);
    char hat2 = (data[12] >> 3 & 0xF);
    char hat3 = (data[10] >> 4 & 0xF);

    hat1North.setValue(     hat1 == 1 );
    hat1NorthEast.setValue( hat1 == 3 );
    hat1East.setValue(      hat1 == 2 );
    hat1SouthEast.setValue( hat1 == 6 );
    hat1South.setValue(     hat1 == 4 );
    hat1SouthWest.setValue( hat1 == 12 );
    hat1West.setValue(      hat1 == 8 );
    hat1NorthWest.setValue( hat1 == 9 );

    hat2North.setValue(     hat2 == 1 );
    hat2NorthEast.setValue( hat2 == 2 );
    hat2East.setValue(      hat2 == 3 );
    hat2SouthEast.setValue( hat2 == 4 );
    hat2South.setValue(     hat2 == 5 );
    hat2SouthWest.setValue( hat2 == 6 );
    hat2West.setValue(      hat2 == 7 );
    hat2NorthWest.setValue( hat2 == 8 );

    hat3North.setValue(     hat3 == 1 );
    hat3NorthEast.setValue( hat3 == 3 );
    hat3East.setValue(      hat3 == 2 );
    hat3SouthEast.setValue( hat3 == 6 );
    hat3South.setValue(     hat3 == 4 );
    hat3SouthWest.setValue( hat3 == 12 );
    hat3West.setValue(      hat3 == 8 );
    hat3NorthWest.setValue( hat3 == 9 );


    
}

}
