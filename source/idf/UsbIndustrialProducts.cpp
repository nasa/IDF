#include "idf/UsbIndustrialProducts.hh"

namespace idf {

UsbIndustrialProducts::UsbIndustrialProducts() :
    UsbDevice("Industrial Products", 8) {}

void UsbIndustrialProducts::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((unsigned)data[1]) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[3]) << 8 | data[2]);
    twist.setValue(((unsigned)data[5]) << 8 | data[4]);

    trigger.setValue(data[6] & 1);

    southWestButton.setValue(data[6] >> 1 & 1);
    northWestButton.setValue(data[6] >> 2 & 1);
    northEastButton.setValue(data[6] >> 3 & 1);
    southEastButton.setValue(data[7] & 1);

    hatNorth.setValue(data[6] >> 4 & 1);
    hatEast.setValue(data[6] >> 5 & 1);
    hatSouth.setValue(data[6] >> 6 & 1);
    hatWest.setValue(data[6] >> 7 & 1);
}

}
