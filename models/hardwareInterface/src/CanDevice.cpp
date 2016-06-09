#include "hardwareInterface/include/CanDevice.hh"
#include <sstream>

namespace idf {

CanDevice::CanDevice(const std::string& id, int networkID, uint32_t flagz,
  int32_t txQueueSize, int32_t rxQueueSize,
  int32_t txTimeout, int32_t rxTimeout) :
    InputDevice(id),
    networkId(networkID),
    flags(flagz),
    transmitQueueSize(txQueueSize),
    receiveQueueSize(rxQueueSize),
    transmitTimeout(txTimeout),
    receiveTimeout(rxTimeout) {}

void CanDevice::open() {

    NTCAN_RESULT result = canOpen(networkId, flags, transmitQueueSize,
      receiveQueueSize, transmitTimeout, receiveTimeout, &ntCanHandle);

    if (result != NTCAN_SUCCESS) {
        std::ostringstream stream;
        stream << "Failed to open " + name + ": NTCAN_ERRNO = " << result;
        throw IOException(stream.str());
    }

    mOpen = true;
}

void CanDevice::close() {
    if (mOpen) {
        canClose(ntCanHandle);
        mOpen = false;
    }
}

}
