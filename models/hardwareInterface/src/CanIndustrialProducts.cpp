#include "CanIndustrialProducts.hh"

#include <iostream>
#include <sstream>

using namespace idf;

const int CanIndustrialProducts::canId = 1553;

CanIndustrialProducts::CanIndustrialProducts(int networkID, uint32_t flagz,
  int32_t txQueueSize, int32_t rxQueueSize, int32_t txTimeout,
  int32_t rxTimeout) :
    CanDevice(networkID, flagz, txQueueSize, rxQueueSize,
      txTimeout, rxTimeout) {}

void CanIndustrialProducts::open() {
    CanDevice::open();

    NTCAN_RESULT result = canSetBaudrate(ntCanHandle, NTCAN_BAUD_1000);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to set baud rate: NTCAN_ERRNO = " << result;
        throw IOException(oss.str());
    }

    result = canIdAdd(ntCanHandle, canId);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to add message ID: NTCAN_ERRNO = " << result;
        throw IOException(oss.str());
    }
}

void CanIndustrialProducts::update() {
    CanDevice::update();

    CMSG message;
    message.id = canId;
    int32_t length = 1;

    NTCAN_RESULT result = canTake(ntCanHandle, &message, &length);
    if (result != NTCAN_SUCCESS) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: NTCAN_ERRNO = " << result;
        throw IOException(oss.str());
    }

    if (!(message.len & NTCAN_NO_DATA)) {
        leftRightPivot.setValue(((message.data[1] & 3) << 8) | message.data[0]);
        forwardBackwardPivot.setValue(((message.data[2] & 0xF) << 6) | (message.data[1] >> 2));
        twist.setValue(((message.data[3] & 0x3F) << 4) | (message.data[2] >> 4));
        hatLeftRightPivot.setValue((message.data[4] << 2) | (message.data[3] >> 6));
        hatUpDownPivot.setValue(((message.data[6] & 3) << 8) | message.data[5]);
        trigger.setValue(message.data[7] & 1);
        hatWest.setValue((message.data[7] >> 1) & 1);
        hatNorth.setValue((message.data[7] >> 2) & 1);
        hatEast.setValue((message.data[7] >> 3) & 1);
        hatSouth.setValue((message.data[7] >> 4) & 1);
        switchUp.setValue((message.data[7] >> 5) & 1);
        switchDown.setValue((message.data[7] >> 6) & 1);
    }
}
