#include <stdio.h>
#include <stdint.h>
#include "idf/UsbMadCatz.hh"

namespace idf {

UsbMadCatz::UsbMadCatz(int vendorID, int productID, const std::string& id) :
    UsbDevice(id, vendorID, productID, 8) {}

UsbMadCatz::UsbMadCatz(int vendorID, int productID, const std::string& id, unsigned length) :
    UsbDevice(id, vendorID, productID, length) {}

void UsbMadCatz::decode(const std::vector<unsigned char>& data) {
    uint16_t value;

    // 10-bits B23 B22 B21 B20 B17 B16 B15 B14 B13 B12
    value = ((uint16_t) data[2] & 0x000f) << 6 |  ((uint16_t)data[1] & 0x00FC) >> 2;
    forwardBackwardPivot.setValue(value);

    // 10-bits  B11 B10 B07 B06 B05 B04 B03 B02 B01 B00
    value = ((uint16_t)data[1] & 0x0003) << 8 | ((uint16_t)data[0] & 0x00ff);
    leftRightPivot.setValue(value);

    value = ((uint16_t)data[4] & 0x000f) << 4 | ((uint16_t)data[3]&0x00f0) >> 4;
    leftThrottle.setValue(value);

    value = ((uint16_t)data[5]&0x000f) << 4 | ((uint16_t)data[4]&0x00f0) >> 4;
    rightThrottle.setValue(value);

    value = ((uint16_t) data[3]&0x000f) << 4 | ((uint16_t)data[2] & 0x00f0) >> 4;
    twist.setValue(value);

    trigger.setValue(data[5] >> 4 & 1);
    button2.setValue(data[5] >> 5 & 1);
    button3.setValue(data[5] >> 6 & 1);
    button4.setValue(data[5] >> 7 & 1);
    button5.setValue(data[6] >> 0 & 1);
    button6.setValue(data[6] >> 1 & 1);
    button7.setValue(data[6] >> 2 & 1);
    button8.setValue(data[6] >> 3 & 1);
    button9.setValue(data[6] >> 4 & 1);
    button10.setValue(data[6] >> 5 & 1);
    button11.setValue(data[6] >> 6 & 1);
    buttonX.setValue(data[7] >> 1 & 1);

    // hat is B75 B74 B73 B72 and all 1's by default
    unsigned int hat = ((uint16_t) data[7] & 0x3c) >> 2;

    hatNorth.setValue(hat == 1);
    hatNorthEast.setValue(hat == 2);
    hatEast.setValue(hat == 3);
    hatSouthEast.setValue(hat == 4);
    hatSouth.setValue(hat == 5);
    hatSouthWest.setValue(hat == 6);
    hatWest.setValue(hat == 7);
    hatNorthWest.setValue(hat == 8);

    scrollUp.setValue(data[6] >> 7 & 1);
    scrollDown.setValue(data[7] >> 0 & 1);
}

}
