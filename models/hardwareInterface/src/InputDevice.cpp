#include "InputDevice.hh"
#include "IOException.hh"

#include <sstream>

using namespace idf;

InputDevice::InputDevice() :
    mOpen(false),
    delay(0),
    enabled(true) {}

bool InputDevice::isOpen() const {
    return mOpen;
}

void InputDevice::update() {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Device is not open.";
        throw IOException(oss.str());
    }
}
