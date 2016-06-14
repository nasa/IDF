/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(hardwareInterface/src/UsbDevice.cpp)
(hardwareInterface/src/hidapi.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbDevice.cpp}
 * @trick_link_dependency{hardwareInterface/src/hidapi.cpp}
 */

#ifndef _USB_DEVICE_HH_
#define _USB_DEVICE_HH_

#include "hardwareInterface/include/InputDevice.hh"

#include <vector>
#include <string>

#ifndef TRICK_ICG
#ifndef SWIG
#include "hidapi/hidapi/hidapi.h"
#endif
#endif

namespace idf {

/**
 * abstract base class for all USB input devices. Subclasses should usually
 * represent a specific physical device (WingMan, SpaceExplorer, etc) and
 * implement logic to fulfill the contract of open(). They should
 * also usually derive from the appropriate class from the %Input Abstraction
 * Layer, as well as be concrete.
 *
 * @author Derek Bankieris
 */
class UsbDevice : public InputDevice {

    public:

    /**
     * constructs a new instance whose open() will look for a USB device with the @a vendorID and @a productID
     *
     * @param name the name of this device
     * @param vendorID the target USB device's vendorID
     * @param productID the target USB device's productID
     * @param packetLength @copydoc packetLength
     */
    UsbDevice(const std::string& name, int vendorID, int productID, unsigned packetLength);

    /** destructs this instance */
    virtual ~UsbDevice();

    /**
     * determines whether or not this device is connected to the computer
     *
     * @return @c true if this device is plugged in
     */
    virtual bool isConnected();

    virtual void open();
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

    virtual std::vector<std::vector<unsigned char> > read();

    private:

    /** device path and handle information */
    class DeviceTag {

        public:

        /** path to the device */
        std::string path;

        #ifndef TRICK_ICG
        /** handle to the device */
        hid_device* handle;

        /**
         * constructor
         *
         * @param deviceHandle handle to the device
         * @param devicePath path to the device
         */
        DeviceTag(hid_device* deviceHandle, std::string& devicePath) :
            path(devicePath),
            handle(deviceHandle) {}
        #endif

    };

    /** number of instances in existance */
    static int instanceCount;

    /** open devices */
    static std::vector<DeviceTag> openDevices;

    /** the length of a packet of data */
    const unsigned packetLength;

    /**
     * reads @a length bytes from this device and stores them in @a buffer
     *
     * @param buffer the location to store the data
     * @param length the number of bytes to read
     *
     * @return the number of bytes read (always non-negative)
     *
     * @throws IOException if an error occurs while reading or if the device is not open
     */
    unsigned read(unsigned char* buffer, size_t length);

    void operator=(const UsbDevice&);

};

}

#endif
