#include "InputDevice.hh"
#include "IOException.hh"

#include <sstream>

using namespace idf;

InputDevice::InputDevice() :
    mOpen(false) {}

bool InputDevice::isOpen() {
    return mOpen;
}

void InputDevice::update() {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << "Device is not open.";
        throw IOException(oss.str().c_str());
    }
}
