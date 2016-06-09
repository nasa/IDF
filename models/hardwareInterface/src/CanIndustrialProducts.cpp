#include "hardwareInterface/include/CanIndustrialProducts.hh"

#include <sstream>

namespace idf {

const int CanIndustrialProducts::canId = 1553;

CanIndustrialProducts::CanIndustrialProducts(int networkID, uint32_t flagz,
  int32_t txQueueSize, int32_t rxQueueSize, int32_t txTimeout, int32_t rxTimeout) :
    CanDevice("Industrial Products", networkID, flagz, txQueueSize, rxQueueSize, txTimeout, rxTimeout) {}

void CanIndustrialProducts::open() {
    CanDevice::open();

    NTCAN_RESULT result = canSetBaudrate(ntCanHandle, NTCAN_BAUD_1000);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream stream;
        stream << " Failed to set baud rate: NTCAN_ERRNO = " << result;
        throw IOException(stream.str());
    }

    result = canIdAdd(ntCanHandle, canId);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream stream;
        stream << " Failed to add message ID: NTCAN_ERRNO = " << result;
        throw IOException(stream.str());
    }
}

std::vector<std::vector<unsigned char> > CanIndustrialProducts::read() {
    CMSG message;
    message.id = canId;
    int32_t length = 1;

    NTCAN_RESULT result = canTake(ntCanHandle, &message, &length);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream stream;
        stream << " Error while reading " << name << ": NTCAN_ERRNO = " << result;
        throw IOException(stream.str());
    }

    std::vector<std::vector<unsigned char> > results;
    if (!(message.len & NTCAN_NO_DATA)) {
        results.push_back(std::vector<unsigned char>(message.data, message.data + message.len));
    }
    return results;
}


void CanIndustrialProducts::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue(((data[1] & 3) << 8) | data[0]);
    forwardBackwardPivot.setValue(((data[2] & 0xF) << 6) | (data[1] >> 2));
    twist.setValue(((data[3] & 0x3F) << 4) | (data[2] >> 4));
    hatLeftRightPivot.setValue((data[4] << 2) | (data[3] >> 6));
    hatUpDownPivot.setValue(((data[6] & 3) << 8) | data[5]);
    trigger.setValue(data[7] & 1);
    hatWest.setValue((data[7] >> 1) & 1);
    hatNorth.setValue((data[7] >> 2) & 1);
    hatEast.setValue((data[7] >> 3) & 1);
    hatSouth.setValue((data[7] >> 4) & 1);
    switchUp.setValue((data[7] >> 5) & 1);
    switchDown.setValue((data[7] >> 6) & 1);
}

}
