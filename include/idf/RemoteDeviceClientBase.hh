/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteDeviceClientBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RemoteDeviceClientBase.cpp}
 */

#ifndef _REMOTE_DEVICE_CLIENT_BASE_HH_
#define _REMOTE_DEVICE_CLIENT_BASE_HH_

#include "idf/Utils.hh"
#include "idf/IOException.hh"

namespace idf {

/**
 * base class for remote device clients
 *
 * @author Derek Bankieris
 */
class RemoteDeviceClientBase {

    public:

    // TODO: fix this rushed interface
    std::string host;
    unsigned short port;

    /**
     * constructs an instance that transmits commands from @a sourceController
     * to the RemoteDeviceServer \<T\> listening on <em>host</em>:<em>port</em>
     *
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

    void open();
    void close();

    /** sends the commands to the server */
    virtual void transmit() = 0;

    protected:

    /** the socket */
    int socketHandle;

    private:

    // TODO: hastily added variable, rethink
    bool mOpen;

    void operator=(const RemoteDeviceClientBase&);

};

}

#endif
