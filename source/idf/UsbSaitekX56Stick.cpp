#include "idf/UsbSaitekX56Stick.hh"

namespace idf {

UsbSaitekX56Stick::UsbSaitekX56Stick() :
    UsbDevice("Saitek Pro Flight X-56 Rhino Stick", 11) {}

UsbSaitekX56Stick::UsbSaitekX56Stick(const std::string& id, unsigned length) :
    UsbDevice(id, length) {}

void UsbSaitekX56Stick::decode(const std::vector<unsigned char>& data) {
    /* Axes */
    leftRightPivot.setValue(       ((unsigned)data[1] << 8) | data[0] );
    forwardBackwardPivot.setValue( ((unsigned)data[3] << 8) | data[2] );

    twist.setValue( ((unsigned)(data[5] & 0xf) << 8) | data[4]);

    thumbLeftRightPivot.setValue( data[9] );
    thumbForwardBackwardPivot.setValue( data[10] );

    /* Buttons*/
    trigger1.setValue( data[6]      & 0x1 );
    trigger2.setValue( data[6] >> 5 & 0x1 );

    buttonA.setValue( data[6] >> 1 & 0x1 );
    buttonB.setValue( data[6] >> 2 & 0x1 );
    buttonC.setValue( data[6] >> 3 & 0x1 );
    buttonD.setValue( data[6] >> 4 & 0x1 );

    /* Hats */
    char pov  = data[5] >> 4 & 0xF;
    char hat1 = ((data[7] << 2) | (data[6] >> 6)) & 0xF;
    char hat2 = data[7] >> 2 & 0xF;
    /** @brief POV is an 8-direction hat Starting at North and incrementing
     * values clockwise
     */
    povUpDownPivot.setValue( pov == 1 || pov ==2 || pov ==8 ? 1 : pov >= 4 && pov <=6 ? -1 : 0);
    povLeftRightPivot.setValue( pov >=2 && pov <=4 ? -1 : pov >=6 && pov <= 8 ? 1 : 0);
    povNorth.setValue(     pov == 1 );
    povNorthEast.setValue( pov == 2 );
    povEast.setValue(      pov == 3 );
    povSouthEast.setValue( pov == 4 );
    povSouth.setValue(     pov == 5 );
    povSouthWest.setValue( pov == 6 );
    povWest.setValue(      pov == 7 );
    povNorthWest.setValue( pov == 8 );

    /**
     * @brief Hat cardinal directions are encoded on individual bits. Ordinal
     * directions are encoded as combinations of the cardinal bits.
     */
    hat1UpDownPivot.setValue( hat1 & 0x1 ? 1 : hat1 & 0x4 ? -1 : 0);
    hat1LeftRightPivot.setValue( hat1 & 0x8 ? 1 : hat1 & 0x2 ? -1 : 0);
    hat1North.setValue(     hat1 == 1 );
    hat1NorthEast.setValue( hat1 == 3 );
    hat1East.setValue(      hat1 == 2 );
    hat1SouthEast.setValue( hat1 == 6 );
    hat1South.setValue(     hat1 == 4 );
    hat1SouthWest.setValue( hat1 == 12 );
    hat1West.setValue(      hat1 == 8 );
    hat1NorthWest.setValue( hat1 == 9 );

    hat2UpDownPivot.setValue( hat2 & 0x1 ? 1 : hat2 & 0x4 ? -1 : 0);
    hat2LeftRightPivot.setValue( hat2 & 0x8 ? 1 : hat2 & 0x2 ? -1 : 0);
    hat2North.setValue(     hat2 == 1 );
    hat2NorthEast.setValue( hat2 == 3 );
    hat2East.setValue(      hat2 == 2 );
    hat2SouthEast.setValue( hat2 == 6 );
    hat2South.setValue(     hat2 == 4 );
    hat2SouthWest.setValue( hat2 == 12 );
    hat2West.setValue(      hat2 == 8 );
    hat2NorthWest.setValue( hat2 == 9 );
}

}