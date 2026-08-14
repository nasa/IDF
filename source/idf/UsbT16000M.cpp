#include "idf/UsbT16000M.hh"

namespace idf {

UsbT16000M::UsbT16000M() :
    UsbDevice("ThrustMaster T.16000M", 9) {}

void UsbT16000M::decode(const std::vector<unsigned char> & data)
{
    trigger.setValue( data[0] & 0x1 );
    middleButton.setValue( data[0] >> 1 & 0x1 );
    leftButton.setValue(   data[0] >> 2 & 0x1 );
    rightButton.setValue(  data[0] >> 3 & 0x1 );
    button5.setValue(  data[0] >> 4 & 0x1 );
    button6.setValue(  data[0] >> 5 & 0x1 );
    button7.setValue(  data[0] >> 6 & 0x1 );
    button8.setValue(  data[0] >> 7 & 0x1 );

    button9.setValue(  data[1] & 0x1 );
    button10.setValue( data[1] >> 1 & 0x1 );
    button11.setValue( data[1] >> 2 & 0x1 );
    button12.setValue( data[1] >> 3 & 0x1 );
    button13.setValue( data[1] >> 4 & 0x1 );
    button14.setValue( data[1] >> 5 & 0x1 );
    button15.setValue( data[1] >> 6 & 0x1 );
    button16.setValue( data[1] >> 7 & 0x1 );

    int hat = (data[2]) & 0xF;

    hatNorth.setValue(hat == 0);
    hatNorthEast.setValue(hat == 1);
    hatEast.setValue(hat == 2);
    hatSouthEast.setValue(hat == 3);
    hatSouth.setValue(hat == 4);
    hatSouthWest.setValue(hat == 5);
    hatWest.setValue(hat == 6);
    hatNorthWest.setValue(hat == 7);

    // the 2 most significant bits are padding
    leftRightPivot.setValue( (unsigned)(data[4] & 0x3F) << 8 | data[3] );
    forwardBackwardPivot.setValue( (unsigned)(data[6] & 0x3F) << 8 | data[5] );

    twist.setValue( data[7] );
    slider.setValue( data[8] );
}

} // namespace idf
