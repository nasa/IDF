#include "idf/UsbThrustMasterAvaBase.hh"

namespace idf {

UsbThrustMasterAvaBase::UsbThrustMasterAvaBase() :
    UsbDevice("ThrustMaster AVA Base", 64) {}

void UsbThrustMasterAvaBase::decode(const std::vector<unsigned char>& data) {
    if (data[0] != 1) return;

    trigger.setValue(data[1] & 0x1);
    button2.setValue(data[1] >> 1 & 0x1);
    button3.setValue(data[1] >> 2 & 0x1);
    button4.setValue(data[1] >> 3 & 0x1);
    button5.setValue(data[1] >> 4 & 0x1);
    button6.setValue(data[1] >> 5 & 0x1);
    button7.setValue(data[1] >> 6 & 0x1);
    button8.setValue(data[1] >> 7 & 0x1);

    button9.setValue(data[2] & 0x1);
    button10.setValue(data[2] >> 1 & 0x1);
    button11.setValue(data[2] >> 2 & 0x1);
    button12.setValue(data[2] >> 3 & 0x1);
    button13.setValue(data[2] >> 4 & 0x1);
    button14.setValue(data[2] >> 5 & 0x1);
    button15.setValue(data[2] >> 6 & 0x1);
    button16.setValue(data[2] >> 7 & 0x1);

    button17.setValue(data[3] & 0x1);
    button18.setValue(data[3] >> 1 & 0x1);
    button19.setValue(data[3] >> 2 & 0x1);
    button20.setValue(data[3] >> 3 & 0x1);
    button21.setValue(data[3] >> 4 & 0x1);
    button22.setValue(data[3] >> 5 & 0x1);
    button23.setValue(data[3] >> 6 & 0x1);
    button24.setValue(data[3] >> 7 & 0x1);

    button25.setValue(data[4] & 0x1);
    button26.setValue(data[4] >> 1 & 0x1);
    button27.setValue(data[4] >> 2 & 0x1);
    button28.setValue(data[4] >> 3 & 0x1);
    button29.setValue(data[4] >> 4 & 0x1);
    button30.setValue(data[4] >> 5 & 0x1);
    button31.setValue(data[4] >> 6 & 0x1);
    button32.setValue(data[4] >> 7 & 0x1);

    unsigned int hat = data[5] & 0xF;

    hatNorth.setValue(hat == 0);
    hatNorthEast.setValue(hat == 1);
    hatEast.setValue(hat == 2);
    hatSouthEast.setValue(hat == 3);
    hatSouth.setValue(hat == 4);
    hatSouthWest.setValue(hat == 5);
    hatWest.setValue(hat == 6);
    hatNorthWest.setValue(hat == 7);

    leftRightPivot.setValue(data[7] << 8 | data[6]);
    forwardBackwardPivot.setValue(data[9] << 8 | data[8]);
    twist.setValue(data[11] << 8 | data[10]);

    leftRightThumbstickPivot.setValue(data[13] << 8 | data[12]);
    forwardBackwardThumbstickPivot.setValue(data[15] << 8 | data[14]);
    rotationZ.setValue(data[17] << 8 | data[16]);

    slider.setValue(data[19] << 8 | data[18]);
    dial.setValue(data[21] << 8 | data[20]);
}

} // namespace idf
