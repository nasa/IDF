/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDevice.cpp)
(idf/hidapi.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDevice.cpp}
 * @trick_link_dependency{idf/hidapi.cpp}
 */

#ifndef USB_DEVICE_HH
#define USB_DEVICE_HH

#include "idf/InputDevice.hh"

#include <vector>
#include <string>

#include "hidapi/hidapi/hidapi.h"

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

    /**
     * sets the path at which this device can be found. This path will be used
     * on the next call to open().
     *
     * @param path @copydoc devicePath
     */
    virtual void setPath(const std::string& path);

    virtual void open();
    virtual void close();

    protected:

    /** vendor ID, used to lookup this device in the USB hierarchy */
    const int vendorId;

    /** product IDs, used to lookup this device in the USB hierarchy */
    std::vector<int> productIds;

    /** handle to the device */
    hid_device* hidDevice;

    virtual std::vector<std::vector<unsigned char> > read();

    private:

    /** device path and handle information */
    class DeviceTag {

        public:

        /** path to the device */
        std::string path;

        /** handle to the device */
        hid_device* handle;

        /**
         * constructor
         *
         * @param deviceHandle handle to the device
         * @param devicePath @copydoc devicePath
         */
        DeviceTag(hid_device* deviceHandle, const std::string& devicePath) :
            path(devicePath),
            handle(deviceHandle) {}

    };

    /** number of instances in existance */
    static int instanceCount;

    /** open devices */
    static std::vector<DeviceTag> openDevices;

    /** the length of a packet of data */
    const unsigned packetLength;

    /** the device path (example: /dev/hidraw0) */
    std::string devicePath;

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

    /**
     * determines if a device's vendor and product IDs match this instance
     *
     * @param deviceInfo the device's vendor and product IDs
     * @return true if this instance represents a device with the given vendor and product ID
     */
    bool deviceMatches(const struct hid_device_info& deviceInfo) const;

    /**
     * opens the device at path
     *
     * @param path @copydoc devicePath
     */
    void open(const std::string& path);

    /**
     * determines if the device at path has been opened
     *
     * @param path @copydoc devicePath
     *
     * @return true if the path is open
     */
    bool isPathOpen(const std::string& path) const;

    void operator=(const UsbDevice&);

};

}

#endif
