/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/RemoteExtreme3dPro.cpp))
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
     * a server which accepts and manages connections from multiple
     * {@link Client}s
     *
     * @author Derek Bankieris
     */
    class RemoteExtreme3dProServer : public Extreme3dPro, public RemoteDeviceServer<RemoteExtreme3dProCommands> {

        public:

        /**
         * constructs an instance which listens for connections on
         * <code>port</code>
         *
         * @param port the port over which to listen for connections
         */
        RemoteExtreme3dProServer(unsigned short port = 0);

        void update();

    };

#ifdef SWIG
class RemoteExtreme3dProClient;
%template (RemoteDeviceClient_RemoteExtreme3dPro) RemoteDeviceClient<Extreme3dPro, RemoteExtreme3dProCommands, RemoteExtreme3dProClient>;
#endif
    /**
     * transmits commands from a contained {@link Extreme3dPro} to a
     * <code>RemoteExtreme3dProServer</code>
     *
     * @author Derek Bankieris
     */
    class RemoteExtreme3dProClient : public RemoteDeviceClient<Extreme3dPro, RemoteExtreme3dProCommands, RemoteExtreme3dProClient> {

        public:

        /**
         * constructs an instance that transmits commands from
         * <code>extreme3dPro</code> to the <code>RemoteExtreme3dProServer</code>
         * listening on <code>host</code>:<code>port</code>
         *
         * @param extreme3dPro the command source
         * @param host the name or ip address of the server host machine
         * @param port the port on which the server is listening
         */
        RemoteExtreme3dProClient(const Extreme3dPro& extreme3dPro,
          const std::string host, unsigned short port);

        /**
         * packs commands from <code>extreme3dPro</code> into
         * <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param extreme3dPro the controller whose commands are to be packed
         */
        static void packCommands(RemoteExtreme3dProCommands& commands,
          const Extreme3dPro& extreme3dPro);

        private:
        void operator=(const RemoteExtreme3dProClient&);

    };

//};

}

#endif
