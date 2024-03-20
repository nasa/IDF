/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/EthernetDevice.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/EthernetDevice.cpp}
 */

#ifndef ETHERNET_DEVICE_HH
#define ETHERNET_DEVICE_HH

#include "idf/InputDevice.hh"

#include <string>

namespace idf {

/**
 * @brief abstract base class for all ethernet input devices. Subclasses should usually
 * represet a specific physical device and implement logic to fulfill the contract of
 * open(). They should also usually derive from the appropriate class from the %Input
 * Abstration Layer, as well as be concrete.
 * 
 * @author  Philip Kunz
 */
class EthernetDevice : public InputDevice {

    public:

    /**
     * @brief constructs a new instance whose open() will open the UDP port at
     * @a ipAddress: @a port
     * 
     * @param ipAddress the ipaddress of this device
     * @param port the port number of this device
     */
    EthernetDevice(const std::string& name, const std::string& ipAddress, const int port);

    virtual ~EthernetDevice() {};
    
    virtual void open();
    virtual void close();

    using InputDevice::read;

    protected:

    /** network socket to the device */
    int socket;

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
    virtual int read(unsigned char *buffer, size_t length);

    /**
     * writes @a length bytes from @a buffer to this device
     *
     * @param buffer the location of the data to write
     * @param length the number of bytes to write
     *
     * @return the number of bytes written (always non-negative)
     *
     * @throws IOException if an error occurs while writing or if the device is not open
     */
    virtual int write(const void *buffer, size_t length);

    /** IP Address to the device */
    std::string ipAddress;

    /** IP Port to the device */
    int port;

};

} // namespace

#endif