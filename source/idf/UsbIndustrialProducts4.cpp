#include "idf/UsbIndustrialProducts4.hh"

namespace idf {

UsbIndustrialProducts4::UsbIndustrialProducts4() :
    UsbDevice("Industrial Products 4", 11) {}

void UsbIndustrialProducts4::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((unsigned)data[1]) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[3]) << 8 | data[2]);
    twist.setValue(((unsigned)data[5]) << 8 | data[4]);

    hatLeftRightPivot.setValue(((unsigned)data[7]) << 8 | data[6]);
    hatUpDownPivot.setValue(((unsigned)data[9]) << 8 | data[8]);

    trigger.setValue(data[10] & 1);
    grip.setValue(data[10] >> 1 & 1);
    switchUp.setValue(data[10] >> 2 & 1);
    switchDown.setValue(data[10] >> 3 & 1);
    button1.setValue(data[10] >> 4 & 1);
    button2.setValue(data[10] >> 5 & 1);

}

}
