#include "idf/UsbWarthogStickBase.hh"

namespace idf
{

UsbWarthogStickBase::UsbWarthogStickBase() :
    UsbDevice("ThrustMaster Warthog Stick", 12) {}

void UsbWarthogStickBase::decode(const std::vector<unsigned char> & data)
{
    if(data[0] != 1) return;

    trigger.setValue( data[1] & 0x1 );
    button2WeaponRelease.setValue( data[1] >> 1 & 0x1 );
    button3NoseSteering.setValue( data[1] >> 2 & 0x1 );
    button4Paddle.setValue( data[1] >> 3 & 0x1 );
    button5MasterMode.setValue( data[1] >> 4 & 0x1 );
    button6Trigger2nd.setValue( data[1] >> 5 & 0x1 );
    button7TmsUp.setValue( data[1] >> 7 & 0x1 );
    button8TmsRight.setValue( data[1] >> 6 & 0x1 );

    button9TmsDown.setValue( data[2] & 0x1 );
    button10TmsLeft.setValue( data[2] >> 1 & 0x1 );
    button11DmsUp.setValue( data[2] >> 2 & 0x1 );
    button12DmsRight.setValue( data[2] >> 3 & 0x1 );
    button13DmsDown.setValue( data[2] >> 4 & 0x1 );
    button14DmsLeft.setValue( data[2] >> 5 & 0x1 );
    button15CmsForward.setValue( data[2] >> 7 & 0x1 );
    button16CmsRight.setValue( data[2] >> 6 & 0x1 );

    button17CmsBack.setValue( data[3] & 0x1 );
    button18CmsLeft.setValue( data[3] >> 1 & 0x1 );
    button19CmsPush.setValue( data[3] >> 2 & 0x1 );
    // 1 bit padding before Hat

    int hat = (data[3] >> 4) & 0xF;

    hatNorth.setValue(hat == 0);
    hatNorthEast.setValue(hat == 1);
    hatEast.setValue(hat == 2);
    hatSouthEast.setValue(hat == 3);
    hatSouth.setValue(hat == 4);
    hatSouthWest.setValue(hat == 5);
    hatWest.setValue(hat == 6);
    hatNorthWest.setValue(hat == 7);

    leftRightPivot.setValue(((unsigned)data[5] & 0xFF) << 8 | data[4]);
    forwardBackwardPivot.setValue(((unsigned)data[7] & 0xFF) << 8 | data[6]);
}

} // namespace idf
