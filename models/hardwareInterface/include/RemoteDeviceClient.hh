/**
 * PURPOSE:
 * ()
 */

#ifndef _REMOTE_DEVICE_CLIENT_HH_
#define _REMOTE_DEVICE_CLIENT_HH_

#include "RemoteDeviceClientBase.hh"
#include "RemoteDeviceServerBase.hh"
#include "inputAbstraction/include/Utils.hh"
#include "IOException.hh"

#include <iostream>
#include <sstream>
#include <exception>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

namespace idf {

/**
 * transmits commands from a contained <code>T</code> to a corresponding
 * <code>RemoteDeviceServer<T></code>
 *
 * @author Derek Bankieris
 */
template <class T, class U, class DerivedClass>
class RemoteDeviceClient : public RemoteDeviceClientBase {

    public:

    /** the controller whose commands are to be transmitted */
    const T& controller;

    /**
     * constructs an instance that transmits commands from
     * <code>sourceController</code> to the <code>RemoteDeviceServer<T></code>
     * listening on <code>host</code>:<code>port</code>
     *
     * @param sourceController the command source
     * @param hostName the name or ip address of the server host machine
     * @param hostPort the port on which the server is listening
     */
    RemoteDeviceClient(const T& sourceController, const std::string hostName, unsigned short hostPort) :
        RemoteDeviceClientBase(hostName, hostPort),
        controller(sourceController) {}

    /** destructor */
    virtual ~RemoteDeviceClient() {}

    // TODO: fix this crappy interface
    /*void setPort(unsigned short hostPort) {
        port = hostPort;
    }
    void setHost(std::string hostName) {
        host = hostName;
    }

    bool isOpen() {
        return mOpen;
    }*/

    /** sends the commands to the server */
    void transmit() {
        RemoteDeviceClientBase::transmit();

        U commands;
        packCommands(commands, controller);

        if (write(socketHandle, &commands, sizeof(commands)) == -1) {
            mOpen = false;
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to write: " << strerror(errno);
            throw IOException(oss.str());
        }
    }


    protected:

    /**
     * packs commands from <code>controller</code> into <code>commands</code>
     *
     * @param commands the structure into which the commands are packed
     * @param controller the controller whose commands are to be packed
     */
    static void packCommands(U& commands, const T& controller) {
        DerivedClass::packCommands(commands, controller);
    };

    /**
     * packs the normalized <code>value</code> into a short
     *
     * @param value the normalized value
     *
     * @return the packed value
     */
    static unsigned char pack(double value) {
        return (signed char)(bound(value) * RemoteDeviceServerBase::serializationFactor);
    }

    private:

    // hastily added variable, rethink
    bool mOpen;

    void operator=(const RemoteDeviceClient&);

};

}

#endif
