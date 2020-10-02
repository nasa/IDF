#include "idf/UsbIndustrialProducts3.hh"

namespace idf {

UsbIndustrialProducts3::UsbIndustrialProducts3() :
    UsbDevice("Industrial Products 3", 12) {
}

void UsbIndustrialProducts3::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((unsigned)data[1]) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[3]) << 8 | data[2]);
    twist.setValue(((unsigned)data[5]) << 8 | data[4]);

    hatLeftRightPivot.setValue(((unsigned)data[7]) << 8 | data[6]);
    hatUpDownPivot.setValue(((unsigned)data[9]) << 8 | data[8]);

    trigger.setValue(data[10] >> 7 & 1);
    button.setValue(data[10] >> 6 & 1);
    switchDown.setValue(data[10] >> 5 & 1);
    switchUp.setValue(data[10] >> 4 & 1);

    hatWest.setValue(data[10] >> 3 & 1);
    hatSouth.setValue(data[10] >> 2 & 1);
    hatEast.setValue(data[10] >> 1 & 1);
    hatNorth.setValue(data[10] & 1);
}

}
