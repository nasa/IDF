/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/RemoteDeviceClientBase.cpp))
 */

#ifndef _REMOTE_DEVICE_CLIENT_BASE_HH_
#define _REMOTE_DEVICE_CLIENT_BASE_HH_

#include "inputAbstraction/include/Utils.hh"
#include "hardwareInterface/include/IOException.hh"

namespace idf {

/**
 * @author Derek Bankieris
 */
class RemoteDeviceClientBase {

    public:

    // TODO: fix this rushed interface
    std::string host;
    unsigned short port;

    /**
     * constructs an instance that transmits commands from
     * <code>sourceController</code> to the <code>RemoteDeviceServer<T></code>
     * listening on <code>host</code>:<code>port</code>
     *
     * @param sourceController the command source
     * @param host the name or ip address of the server host machine
     * @param port the port on which the server is listening
     */
    RemoteDeviceClientBase(const std::string host, unsigned short port);

    /** destructor */
    virtual ~RemoteDeviceClientBase();

    // TODO: fix this crappy interface
    void setPort(unsigned short port);
    void setHost(std::string host);
    bool isOpen();

    /**
     * attempts to connect to the host returned by <code>getHost<code> on the port
     * returned by <code>getPort()</code>
     */
    void open();
    void close();

    /** sends the commands to the server */
    virtual void transmit() = 0;

    protected:

    /** the socket */
    int socketHandle;

    private:

    // hastily added variable, rethink
    bool mOpen;

    void operator=(const RemoteDeviceClientBase&);

};

}

#endif
