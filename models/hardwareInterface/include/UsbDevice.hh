/*
 PURPOSE:
 ()

 LIBRARY DEPENDENCIES:
 ((hardwareInterface/src/UsbDevice.cpp)
  (hardwareInterface/src/hidapi.c))
*/

#ifndef _USB_DEVICE_HH_
#define _USB_DEVICE_HH_

#include "InputDevice.hh"

#include <vector>

#ifndef TRICK_ICG
#ifndef SWIG
#include "hidapi/hidapi/hidapi.h"
#endif
#endif

namespace idf {

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

    /** destructor */
    virtual ~UsbDevice();

    /** opens this device for communication */
    virtual void open();

    /** closes this device */
    virtual void close();

    protected:

    /** vendor ID, used to lookup this device in the USB hierarchy */
    int vendorId;

    /** product IDs, used to lookup this device in the USB hierarchy */
    std::vector<int> productIds;

#ifndef TRICK_ICG
    /** handle to the device */
    hid_device* hidDevice;
#endif

    /**
     * reads <code>length</code> bytes from this device and stores them in
     * <code>buffer</code>
     *
     * @param buffer the location to store the data
     * @param length the number of bytes to read
     *
     * @return the number of bytes read (always non-negative)
     *
     * @throws IOException if an error occurs while reading or if the device
     * is not open
     */
    virtual int read(unsigned char *buffer, size_t length);

    private:

    /** number of instances in existance */
    static int instanceCount;

};

}

#endif
