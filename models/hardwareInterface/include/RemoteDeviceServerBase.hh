/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/RemoteDeviceServerBase.cpp))
 */

#ifndef _REMOTE_DEVICE_SERVER_BASE_HH_
#define _REMOTE_DEVICE_SERVER_BASE_HH_

#include "InputDevice.hh"

namespace idf {

class RemoteDeviceServerBase : public InputDevice {

    public:

    virtual ~RemoteDeviceServerBase();

    /**
     * the factor to use when packing and unpacking commands, facilitating
     * conversion between double and short
     */
    static const double serializationFactor;

    /**
     * begins listening for client connections on the port returned by
     * <code>getPort()</code>
     */
    void open();

    /**
     * terminates existing client connections and stops listening for new ones
     */
    void close();

    /**
     * sets the port on which this instance should listen for connections the
     * next time <code>open()</code> is called. A value of <code>0</code>
     * indicates that the first available port should be used.
     *
     * @param port the port on which to listen
     */
    void setPort(unsigned short port);

    /**
     * returns the actual port on which this instance is listening for client
     * connections if <code>isOpen</code> returns <code>true</code>. Returns
     * the designated port otherwise.
     *
     * @return the listening port
     */
    unsigned short getPort() const;

    protected:

    /** the listening socket */
    int socket;

    /**
     * constructs an instance which listens for connections on
     * <code>port</code>
     *
     * @param port the port over which to listen for connections
     */
    RemoteDeviceServerBase(unsigned short port = 0);

    private:

    /** the port over which to listen for clients */
    unsigned short port;

};

}

#endif
