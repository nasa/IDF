#include "idf/UsbDualShock.hh"

namespace idf {

UsbDualShock::UsbDualShock(const std::string& deviceName, unsigned length) :
    UsbDevice(deviceName, length) {}

}
