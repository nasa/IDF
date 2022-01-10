/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDevice.cpp)
(idf/hidapi.c)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDevice.cpp}
 * @trick_link_dependency{idf/hidapi.c}
 */

#ifndef USB_DEVICE_HH
#define USB_DEVICE_HH

#include "idf/InputDevice.hh"

#include <map>
#include <string>
#include <vector>

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

    /** properties that identify a particular USB product */
    class Identification {

        public:

        /** vendor ID */
        int vendorId;

        /** product ID */
        int productId;

        /** interface number */
        int interfaceNumber;

        Identification(const struct hid_device_info& info) :
            vendorId(info.vendor_id),
            productId(info.product_id),
            interfaceNumber(info.interface_number) {}

        Identification(int vendor, int product, int interface) :
            vendorId(vendor),
            productId(product),
            interfaceNumber(interface) {}

        bool operator==(const Identification& other) {
            return vendorId == other.vendorId
                && productId == other.productId
                && interfaceNumber == other.interfaceNumber;
        }

    };

    /**
     * constructor
     *
     * @param name @copydoc InputDevice::name
     * @param packetLength @copydoc packetLength
     */
    UsbDevice(const std::string& name, unsigned packetLength);

    /** destructor, calls #close */
    virtual ~UsbDevice();

    /**
     * determines whether or not this device is connected to the computer
     *
     * @return @c true if this device is plugged in
     */
    virtual bool isConnected();

    /**
     * sets @a serialNumber as an additional constraint when searching for matching devices
     *
     * @param serialNumber @copydoc serialNumber
     */
    virtual void setSerialNumber(const std::wstring& serialNumber);

    /**
     * sets @a path as an additional constraint when searching for matching devices
     *
     * @param path @copydoc path
     */
    virtual void setPath(const std::string& path);

    /**
     * adds @a identifcation as a new ID that this device can match against
     *
     * @param identification @copydoc Identification
     */
    virtual void addIdentification(const Identification& identification);

    /**
     * gets the actual path this instance was bound to during #open
     *
     * @return the system path to this device or an empty string if this instance is not yet bound
     */
    virtual std::string getPath();

    virtual void open();
    virtual void close();

    protected:

    /** handle to the device */
    hid_device* hidDevice; // trick_io(**)

    virtual std::vector<std::vector<unsigned char> > read();

    private:

    /** number of instances in existance */
    static int instanceCount;

    /** open devices and their paths */
    static std::map<UsbDevice*, std::string> openDevices;

    /** list of known vendor, product, and interface numbers for all supported devices */
    std::map<std::string, std::vector<Identification> > identifications;

    /** length of a packet of data */
    const unsigned packetLength;

    /** serial number */
    std::wstring serialNumber;

    /** path (example: /dev/hidraw0) */
    std::string path;

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
     * determines if a device can be serviced by this instance based on its
     * vendor ID, product ID, interface number, serial number, and path
     *
     * @param deviceInfo the device's information
     *
     * @return @a true if the device matches
     */
    bool deviceMatches(const struct hid_device_info& deviceInfo);

    /**
     * opens the device at @a path
     *
     * @param path @copydoc path
     */
    void open(const std::string& path);

    /**
     * returns the instance (if any) that is open at @a path
     *
     * @param path @copydoc path
     *
     * @return the open instance or @a NULL
     */
    UsbDevice* getInstanceAtPath(const std::string& path) const;

    /**
     * returns an absolute path to @a path, resolving '.', '..', and symbolic links
     *
     * @return the resolved path
     */
    std::string resolvePath(const std::string& path) const;

    std::string getDeviceName(const Identification& info);

    void operator=(const UsbDevice&);

};

}

#endif
