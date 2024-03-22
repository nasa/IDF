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
    EthernetDevice(const std::string& name);

    virtual ~EthernetDevice() {
        close();
    };
    
    virtual void open();
    virtual void close();

    using InputDevice::read;

    private:

    /** the name or ip address of the server */
    std::string serverName;

    /** the port on which the server is listening */
    unsigned short serverPort;

    /** Number of times to retry establishing the initial connection */
    int retryLimit;

    /** the socket */
    int socketHandle;
    
    protected:

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

    
    /**
     * sets the retry limit for initial connection
     *
     * @param limit @copydoc retryLimit
     */
    void setRetryLimit(const int limit) {
        retryLimit = limit;
    }

    /**
     * sets the host to which this instance will attempt to connect the next
     * time open() is called
     *
     * @param host @copydoc serverName
     */
    void setHost(const std::string& host) {
        serverName = host;
    }

    /**
     * sets the server port to which this instance will attempt to connect the
     * next time open() is called
     *
     * @param port @copydoc serverPort
     */
    void setPort(unsigned short port) {
        serverPort = port;
    }

};

} // namespace

#endif