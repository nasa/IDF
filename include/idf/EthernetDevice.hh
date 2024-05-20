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
#include <netinet/in.h>
#include <ctime>

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
    EthernetDevice(const std::string& name, const std::string& host, unsigned short port, unsigned packetLength);

    virtual ~EthernetDevice() {
        close();
    };
    
    virtual void open();
    virtual void close();

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

    /**
     * @brief Sets the communications protocol to TCP.
     * default is TCP
     */
    void setTCP() {
        tcp = true;
        sockType = SOCK_STREAM;
    }

    /**
     * @brief Sets the communications protocol to UDP.
     * default is TCP.
     */
    virtual void setUDP() = 0;

    protected:

    /**
     * @brief Sets the communications protocol to UDP.
     * default is TCP.
     * @param greeting message to send to server when connecting
     * @param length of greeting
     */
    void setUDP(const unsigned char* greeting, size_t length) {
        tcp = false;
        sockType = SOCK_DGRAM;
        udpGreeting.reserve(length);
        udpGreeting = std::vector<unsigned char>(greeting, greeting+length);
        printf("UDP Greeting: `%s`\n", &udpGreeting[0]);
        // udpGreetingLen = length;
    }

    virtual std::vector<std::vector<unsigned char> > read();

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
    virtual size_t read(unsigned char *buffer, size_t length);

    /**
     * peeks at up to @a max bytes from this device and stores them in @a buffer
     *
     * @param buffer the location to store the data
     * @param max the number of bytes to read
     *
     * @return the number of bytes peeked (always non-negative)
     *
     * @throws IOException if an error occurs while peeking or if the device is not open
     */
    virtual size_t peek(unsigned char *buffer, size_t max);

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
    virtual size_t write(const void *buffer, size_t length);

    private:

    const unsigned packetLength;

    /** the name or ip address of the server */
    std::string serverName;

    /** the port on which the server is listening */
    unsigned short serverPort;

    /** the socket */
    int socketHandle;

    struct sockaddr_in serverAddr;
    socklen_t serverAddrLen;

    struct sockaddr_in srcAddr;
    socklen_t srcAddrLen;

    /** socket type specifier. Should be set via setTCP or setUDP */
    int sockType;

    /** default to using TCP for communications */
    bool tcp;

    std::vector<unsigned char> udpGreeting;

    std::time_t lastPacketArrived;

};

} // namespace

#endif