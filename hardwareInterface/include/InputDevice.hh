#ifndef _INPUT_DEVICE_HH_
#define _INPUT_DEVICE_HH_

#include <sstream>
#include "IOException.hh"

namespace hardware {

/**
 * abstract base class for all input devices. Subclasses should usually be
 * abstract, represent collections of input devices that communicate via a
 * specific protocol (usb, serial, CAN, TCP/IP, etc), and encapsulate data
 * and functions particular to and shared across all devices of that type.
 *
 * @author Derek Bankieris
 */
class InputDevice {

    public:

    /** constructor */
    InputDevice() :
        mOpen(false) {}

    /** destructs this instance */
    virtual ~InputDevice() {};

    /** opens this device for communication */
    virtual void open() = 0;

    /** closes this device */
    virtual void close() = 0;

    /**
     * returns the open state of this device
     *
     * @return whether or not this device is open
     */
    virtual bool isOpen() {
        return mOpen;
    }

    /**
     * updates this instance so that it reflects the target device's current
     * state
     */
    virtual void update() {
        if (!mOpen) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
                << "Device is not open.";
            throw IOException(oss.str().c_str());
        }
    }

    virtual void printState() = 0;

    protected:

    /** the open state of this device */
    bool mOpen;

};

}

#endif
