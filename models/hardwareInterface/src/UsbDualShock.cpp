#include "hardwareInterface/include/UsbDualShock.hh"

namespace idf {

UsbDualShock::UsbDualShock(const std::string deviceName, int vendorID, int productID, unsigned length) :
    UsbDevice(deviceName, vendorID, productID, length) {}

}
