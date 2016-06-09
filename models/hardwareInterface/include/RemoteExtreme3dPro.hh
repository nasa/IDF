/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/RemoteExtreme3dPro.cpp}
 */

#ifndef _REMOTE_EXTREME_3D_PRO_HH_
#define _REMOTE_EXTREME_3D_PRO_HH_

#include "inputAbstraction/include/Extreme3dPro.hh"
#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"

namespace idf {

//class RemoteExtreme3dPro {

//    public:

    /** structure used to serialze commands */
    /** TODO: fix
     * WARNING: This is, in general, a TERRIBLE approach. Doubles are not safe for
     * network transmission. They're used here because this class is part of an
     * emergency (limited-time) development effort.
     */
    struct RemoteExtreme3dProCommands {
        double forwardBackwardPivot;
        double leftRightPivot;
        double twist;
        double trigger;
        double button2;
        double button3;
        double button4;
        double button5;
        double button6;
        double button7;
        double button8;
        double button9;
        double button10;
        double button11;
        double button12;
        double hatNorth;
        double hatNorthEast;
        double hatEast;
        double hatSouthEast;
        double hatSouth;
        double hatSouthWest;
        double hatWest;
        double hatNorthWest;
        double slider;
    };

#ifdef SWIG
%template (RemoteDeviceServer_RemoteExtreme3dPro) RemoteDeviceServer<RemoteExtreme3dProCommands>;
#endif
    /**
     * a server which accepts and manages connections from multiple clients
     *
     * @author Derek Bankieris
     */
    class RemoteExtreme3dProServer : public Extreme3dPro, public RemoteDeviceServer<RemoteExtreme3dProCommands> {

        public:

        /** @copydoc RemoteDeviceServer */
        RemoteExtreme3dProServer(unsigned short listenPort = 0);

        void update();

    };

#ifdef SWIG
class RemoteExtreme3dProClient;
%template (RemoteDeviceClient_RemoteExtreme3dPro) RemoteDeviceClient<Extreme3dPro, RemoteExtreme3dProCommands>;
#endif
    /**
     * transmits commands from a contained Extreme3dPro to a RemoteExtreme3dProServer
     *
     * @author Derek Bankieris
     */
    class RemoteExtreme3dProClient : public RemoteDeviceClient<Extreme3dPro, RemoteExtreme3dProCommands> {

        public:

        /** @copydoc RemoteDeviceClient::RemoteDeviceClient */
        RemoteExtreme3dProClient(const Extreme3dPro& sourceController, const std::string hostName, unsigned short hostPort);

        void packCommands(RemoteExtreme3dProCommands& commands, const Extreme3dPro& controller);

        private:

        void operator=(const RemoteExtreme3dProClient&);

    };

//};

}

#endif
