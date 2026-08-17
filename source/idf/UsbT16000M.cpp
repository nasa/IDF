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

    bool rightHanded = data[2] >> 5 & 0x1;
    unsigned char leftButtons = 0;
    unsigned char rightButtons = 0;

    if (forceRightHanded && !rightHanded) {
        leftButtons = data[1] >> 2;
        rightButtons = (data[0] >> 4 & 0xF) | (data[1] << 4);
    } else {
        leftButtons = (data[0] >> 4 & 0xF) | (data[1] << 4);
        rightButtons = data[1] >> 2;
    }

    button5.setValue(  leftButtons & 0x1 );
    button6.setValue(  leftButtons >> 1 & 0x1 );
    button7.setValue(  leftButtons >> 2 & 0x1 );
    button8.setValue(  leftButtons >> 3 & 0x1 );
    button9.setValue(  leftButtons >> 4 & 0x1 );
    button10.setValue( leftButtons >> 5 & 0x1 );

    button11.setValue( rightButtons & 0x1 );
    button12.setValue( rightButtons >> 1 & 0x1 );
    button13.setValue( rightButtons >> 2 & 0x1 );
    button14.setValue( rightButtons >> 3 & 0x1 );
    button15.setValue( rightButtons >> 4 & 0x1 );
    button16.setValue( rightButtons >> 5 & 0x1 );

    // rightHandMode bit is not specified in the HID Report Descriptor
    rightHandMode.setValue( rightHanded );

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
