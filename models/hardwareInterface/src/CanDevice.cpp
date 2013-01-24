#include "CanDevice.hh"

#include <iostream>
#include <sstream>

using namespace idf;

CanDevice::CanDevice(int networkID, uint32_t flagz,
  int32_t txQueueSize, int32_t rxQueueSize,
  int32_t txTimeout, int32_t rxTimeout) :
    networkId(networkID),
    flags(flagz),
    transmitQueueSize(txQueueSize),
    receiveQueueSize(rxQueueSize),
    transmitTimeout(txTimeout),
    receiveTimeout(rxTimeout) {}

CanDevice::~CanDevice() {
    close();
}

void CanDevice::open() {

    NTCAN_RESULT result = canOpen(networkId, flags, transmitQueueSize,
      receiveQueueSize, transmitTimeout, receiveTimeout, &ntCanHandle);

    if (result != NTCAN_SUCCESS) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to open device: NTCAN_ERRNO = " << result;
        throw IOException(oss.str().c_str());
    }

    mOpen = true;
}

void CanDevice::close() {
    if (mOpen) {
        canClose(ntCanHandle);
        mOpen = false;
    }
}
