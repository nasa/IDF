#include "idf/UsbSpaceBase.hh"

namespace idf {

UsbSpaceBase::UsbSpaceBase(const std::string& id) :
    UsbDevice(id, 7) {}

void UsbSpaceBase::decode(const std::vector<unsigned char>& data) {
    switch (data[0]) {
        case 1:
            leftRightTranslation.setValue((int)(char)data[2] << 8 | data[1]);
            forwardBackwardTranslation.setValue((int)(char)data[4] << 8 | data[3]);
            upDownTranslation.setValue((int)(char)data[6] << 8 | data[5]);
            break;
        case 2:
            forwardBackwardPivot.setValue((int)(char)data[2] << 8 | data[1]);
            leftRightPivot.setValue((int)(char)data[4] << 8 | data[3]);
            twist.setValue((int)(char)data[6] << 8 | data[5]);
            break;
        case 3:
            processButtons(&data[1]);
            break;
    }
}

}
