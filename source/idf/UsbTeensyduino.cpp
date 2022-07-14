#include "idf/UsbTeensyduino.hh"

namespace idf {

UsbTeensyduino::UsbTeensyduino() :
    UsbDevice("Teensyduino Joystick", 12) {}


UsbTeensyduino::UsbTeensyduino(const std::string& id, unsigned length) :
    UsbDevice(id, length) {}

void UsbTeensyduino::decode(const std::vector<unsigned char>& data) {
    button1.setValue(  data[0]      & 0x1 );
    button2.setValue(  data[0] >> 1 & 0x1 );
    button3.setValue(  data[0] >> 2 & 0x1 );
    button4.setValue(  data[0] >> 3 & 0x1 );
    button5.setValue(  data[0] >> 4 & 0x1 );
    button6.setValue(  data[0] >> 5 & 0x1 );
    button7.setValue(  data[0] >> 6 & 0x1 );
    button8.setValue(  data[0] >> 7 & 0x1 );
    button9.setValue(  data[1]      & 0x1 );
    button10.setValue( data[1] >> 1 & 0x1 );
    button11.setValue( data[1] >> 2 & 0x1 );
    button12.setValue( data[1] >> 3 & 0x1 );
    button13.setValue( data[1] >> 4 & 0x1 );
    button14.setValue( data[1] >> 5 & 0x1 );
    button15.setValue( data[1] >> 6 & 0x1 );
    button16.setValue( data[1] >> 7 & 0x1 );
    button17.setValue( data[2]      & 0x1 );
    button18.setValue( data[2] >> 1 & 0x1 );
    button19.setValue( data[2] >> 2 & 0x1 );
    button20.setValue( data[2] >> 3 & 0x1 );
    button21.setValue( data[2] >> 4 & 0x1 );
    button22.setValue( data[2] >> 5 & 0x1 );
    button23.setValue( data[2] >> 6 & 0x1 );
    button24.setValue( data[2] >> 7 & 0x1 );
    button25.setValue( data[3]      & 0x1 );
    button26.setValue( data[3] >> 1 & 0x1 );
    button27.setValue( data[3] >> 2 & 0x1 );
    button28.setValue( data[3] >> 3 & 0x1 );
    button29.setValue( data[3] >> 4 & 0x1 );
    button30.setValue( data[3] >> 5 & 0x1 );
    button31.setValue( data[3] >> 6 & 0x1 );
    button32.setValue( data[3] >> 7 & 0x1 );

    int hat = (int)(data[4] & 0x0F);

    hatNorth.setValue( hat == 0 );
    hatNorthEast.setValue( hat == 1 );
    hatEast.setValue( hat == 2 );
    hatSouthEast.setValue( hat == 3 );
    hatSouth.setValue( hat == 4 );
    hatSouthWest.setValue( hat == 5 );
    hatWest.setValue( hat == 6 );
    hatNorthWest.setValue( hat == 7 );
    
    x.setValue( ((unsigned)data[5] & 0x3F) << 4 | (data[4] & 0xF0) >> 4);
    y.setValue( (unsigned)data[6] << 2 | (data[5] & 0xC0) >> 6);
    z.setValue( ((unsigned)data[8] & 0x03) << 8 | data[7]);
    zRotate.setValue( ((unsigned)data[9] & 0x0F) << 6 | (data[8] & 0xFC) >> 2);

    sliderLeft.setValue( ((unsigned)data[10] & 0x3F) << 4 | (data[9] & 0xF0) >> 4);
    sliderRight.setValue( (unsigned)data[11] << 2 | (data[10] & 0xC0) >> 6);
}

}
