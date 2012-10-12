/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbDevice.cpp)
    (hardwareInterface/src/hidapi.c))
 */

#ifndef _USB_DEVICE_HH_
#define _USB_DEVICE_HH_

#include "InputDevice.hh"
#include <vector>
#include <stdio.h>
#include <errno.h>

#ifndef TRICK_ICG
#ifndef SWIG
#include "hidapi/hidapi/hidapi.h"
#endif
#endif

namespace hardware {

/**
 * abstract base class for all USB input devices. Subclasses should usually
 * represent a specific physical device (WingMan, SpaceExplorer, etc) and
 * implement logic to fulfill the contract of <code>open</code>. They should
 * also usually derive from the appropriate class from the Input Abstraction
 * Layer, as well as be concrete.
 *
 * @author Derek Bankieris
 */
class UsbDevice : public InputDevice {

    public:

    /**
     * constructs a new instance whose <code>open()</code> will look for a USB
     * device with the <code>vendorID</code> and <code>productID</code>
     *
     * @param vendorID the target USB device's vendorID
     * @param productID the target USB device's productID
     */
    UsbDevice(int vendorID, int productID);

    /** destructs this instance */
    virtual ~UsbDevice();

    virtual void open();

    virtual void close();

    protected:

    /** vendor ID, used to lookup this device in the USB hierarchy */
    int vendorId;

    /** product IDs, used to lookup this device in the USB hierarchy */
    std::vector<int> productIds;

    /** handle to the device */
    hid_device* hidDevice;

    private:

    /** number of instances in existance */
    static int instanceCount;

};

}

#endif
