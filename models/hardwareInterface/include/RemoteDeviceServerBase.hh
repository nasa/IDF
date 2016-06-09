/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/RemoteDeviceServerBase.cpp}
 */

#ifndef _REMOTE_DEVICE_SERVER_BASE_HH_
#define _REMOTE_DEVICE_SERVER_BASE_HH_

#include "hardwareInterface/include/InputDevice.hh"

namespace idf {

class RemoteDeviceServerBase : public InputDevice {

    public:

    /** the factor to use when packing and unpacking commands */
    static const double serializationFactor;

    /** destructor */
    virtual ~RemoteDeviceServerBase();

    /** begins listening for client connections on the port returned by getPort() */
    void open();

    /** terminates existing client connections and stops listening for new ones */
    void close();

    /**
     * sets the port on which this instance should listen for connections the next time open() is called.
     * A value of @c 0 indicates that the first available port should be used.
     *
     * @param port the port on which to listen
     */
    void setPort(unsigned short port);

    /**
     * returns the actual port on which this instance is listening for client connections
     * if isOpen() returns @c true. Returns the designated port otherwise.
     *
     * @return the listening port
     */
    unsigned short getPort() const;

    /**
     * unpacks the @a value packed by RemoteDeviceClient::pack
     *
     * @param value the packed value
     *
     * @return the normalized value
     */
    static double unpack(signed char value);

    protected:

    /** the listening socket */
    int socket;

    /**
     * constructs an instance which listens for connections on @a port
     *
     * @param port @copydoc port
     */
    RemoteDeviceServerBase(unsigned short port = 0);

    private:

    /** the port over which to listen for clients */
    unsigned short port;

};

}

#endif
