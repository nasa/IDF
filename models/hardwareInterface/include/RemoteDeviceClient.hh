/** @trick_parse{everything} */

#ifndef _REMOTE_DEVICE_CLIENT_HH_
#define _REMOTE_DEVICE_CLIENT_HH_

#include "hardwareInterface/include/RemoteDeviceClientBase.hh"
#include "hardwareInterface/include/RemoteDeviceServerBase.hh"
#include "inputAbstraction/include/Utils.hh"
#include "hardwareInterface/include/IOException.hh"

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
 * transmits commands from a contained @a T to a corresponding {@link RemoteDeviceServer}\<T\>
 *
 * @param T @copydoc controller
 * @param U the structure into which commands are packed
 *
 * @author Derek Bankieris
 */
template <class T, class U>
class RemoteDeviceClient : public RemoteDeviceClientBase {

    public:

    /** the controller whose commands are to be transmitted */
    const T& controller;

    /**
     * constructs an instance that transmits commands from @a sourceController
     * to the RemoteDeviceServer \<T\> listening on <em>hostname</em>:<em>hostPort</em>
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
        packCommands(commands);

        if (write(socketHandle, &commands, sizeof(commands)) == -1) {
            mOpen = false;
            throw IOException("Failed to write: " + std::string(strerror(errno)));
        }
    }


    protected:

    /**
     * packs commands from @a controller into @a commands
     *
     * @param commands the structure into which the commands are packed
     */
    virtual void packCommands(U& commands) = 0;

    /**
     * packs the normalized @a value into a @c char
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
