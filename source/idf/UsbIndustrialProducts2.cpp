#include "idf/UsbIndustrialProducts2.hh"

namespace idf {

UsbIndustrialProducts2::UsbIndustrialProducts2(int vendorID, int productID) :
    UsbDevice("Industrial Products 2", vendorID, productID, 8) {
}

void UsbIndustrialProducts2::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((unsigned)data[1]) << 8 | data[0]);
    forwardBackwardPivot.setValue(((unsigned)data[3]) << 8 | data[2]);
    twist.setValue(((unsigned)data[5]) << 8 | data[4]);

    trigger.setValue(data[6] & 1);
    southWestButton.setValue(data[6] >> 1 & 1);
    northWestButton.setValue(data[6] >> 2 & 1);
    northEastButton.setValue(data[6] >> 3 & 1);

    hatNorth.setValue(data[6] & 1);
    hatEast.setValue(data[6] >> 1 & 1);
    hatSouth.setValue(data[6] >> 2 & 1);
    hatWest.setValue(data[6] >> 3 & 1);

    southEastButton.setValue(data[7] & 1);
}

}
