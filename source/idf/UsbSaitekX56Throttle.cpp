#include "idf/UsbSaitekX56Throttle.hh"

namespace idf {

UsbSaitekX56Throttle::UsbSaitekX56Throttle() :
    UsbDevice("Saitek Pro Flight X-56 Rhino Throttle", 13) {}

UsbSaitekX56Throttle::UsbSaitekX56Throttle(const std::string& id, unsigned length) :
    UsbDevice(id, length) {}

void UsbSaitekX56Throttle::decode(const std::vector<unsigned char>& data) {
    leftThrottle.setValue( ((unsigned)data[1] & 0x3) << 8 | data[0] );
    rightThrottle.setValue(((unsigned)data[2] & 0xF) << 6 | data[1] >> 2 );

    buttonE.setValue( data[2] >> 4 & 0x1 );
    buttonF.setValue( data[2] >> 5 & 0x1 );
    buttonG.setValue( data[2] >> 6 & 0x1 );
    buttonH.setValue( data[3]      & 0x1 );
    buttonI.setValue( data[2] >> 7 & 0x1 );
    buttonJ.setValue( data[6] >> 3 & 0x1 );
    buttonK.setValue( data[5] >> 7 & 0x1 );
    buttonL.setValue( data[6]      & 0x1 );

    switch1.setValue( data[3] >> 1 & 0x1 );
    switch2.setValue( data[3] >> 2 & 0x1 );
    switch3.setValue( data[3] >> 3 & 0x1 );
    switch4.setValue( data[3] >> 4 & 0x1 );
    switch5.setValue( data[3] >> 5 & 0x1 );
    switch6.setValue( data[3] >> 6 & 0x1 );

    toggle1.setValue( (data[3] & 0x80) ? 1 : data[4] & 0x1  ? -1 : 0 );
    toggle2.setValue( (data[4] & 0x2)  ? 1 : data[4] & 0x4  ? -1 : 0 );
    toggle3.setValue( (data[4] & 0x8)  ? 1 : data[4] & 0x10 ? -1 : 0 );
    toggle4.setValue( (data[4] & 0x20) ? 1 : data[4] & 0x40 ? -1 : 0 );

    /**
     * @brief Hat cardinal directions are encoded on individual bits. Ordinal
     * directions are encoded as combinations of the cardinal bits.
     */
    char hat3 = (data[4] & 0x7) << 1 | (data[5] >> 7 & 0x1);
    char hat4 = data[5] >> 3 & 0xF;

    hat3North.setValue(     hat3 == 1 );
    hat3NorthEast.setValue( hat3 == 3 );
    hat3East.setValue(      hat3 == 2 );
    hat3SouthEast.setValue( hat3 == 6 );
    hat3South.setValue(     hat3 == 4 );
    hat3SouthWest.setValue( hat3 == 12 );
    hat3West.setValue(      hat3 == 8 );
    hat3NorthWest.setValue( hat3 == 9 );

    hat4North.setValue(     hat4 == 1 );
    hat4NorthEast.setValue( hat4 == 3 );
    hat4East.setValue(      hat4 == 2 );
    hat4SouthEast.setValue( hat4 == 6 );
    hat4South.setValue(     hat4 == 4 );
    hat4SouthWest.setValue( hat4 == 12 );
    hat4West.setValue(      hat4 == 8 );
    hat4NorthWest.setValue( hat4 == 9 );

    scrollUp.setValue(   data[6] >> 1 & 0x1 );
    scrollDown.setValue( data[6] >> 2 & 0x1 );

    slider.setValue( data[6] >> 4 & 0x1 );

    mode.setValue( data[6] & 0x20 ? 1 : data[6] & 0x40 ? 2 : 3 );

    rotary1.setValue( data[7] );
    rotary2.setValue( data[9] );
    rotary3.setValue( data[11] );
    rotary3.setValue( data[12] );

    thumbForwardBackwardPivot.setValue( data[8] );
    thumbUpDownPivot.setValue( data[10] );

}

}