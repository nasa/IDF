/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/RemoteCameraController.cpp))
 */

#ifndef _REMOTE_CAMERA_CONTROLLER_HH_
#define _REMOTE_CAMERA_CONTROLLER_HH_

#include "simulationInterface/include/CameraController.hh"
#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"

namespace idf {

class RemoteCameraController {

    public:

    /** structure used to serialze commands */
    struct Commands {

        /** serialized commanded pan */
        signed char pan;

        /** serialized commanded tilt */
        signed char tilt;

        /** serialized commanded spin */
        signed char spin;

        /** serialized commanded zoom */
        signed char zoom;

    };

    /**
     * a server which accepts and manages connections from multiple
     * {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public CameraController, public RemoteDeviceServer<Commands> {

        public:

        /**
         * constructs an instance which listens for connections on
         * <code>port</code>
         *
         * @param port the port over which to listen for connections
         */
        Server(unsigned short port = 0);

        /**
         * gets the pan value, normalized to [-1, 0, 1]
         *
         * @return the pan of all added camera controllers
         */
        double getCommandedPan() const;

        /**
         * gets the tilt value, normalized to [-1, 0, 1]
         *
         * @return the tilt of all added camera controllers
         */
        double getCommandedTilt() const;

        /**
         * gets the spin value, normalized to [-1, 0, 1]
         *
         * @return the spin of all added camera controllers
         */
        double getCommandedSpin() const;

        /**
         * gets the zoom value, normalized to [-1, 0, 1]
         *
         * @return the zoom of all added camera controllers
         */
        double getCommandedZoom() const;

    };

    /**
     * transmits commands from a contained {@link CameraController} to a
     * <code>Server</code>
     *
     * @author Derek Bankieris
     */
    class Client : public RemoteDeviceClient<CameraController, Commands, Client> {

        public:

        /**
         * constructs an instance that transmits commands from
         * <code>cameraController</code> to the <code>Server</code>
         * listening on <code>host</code>:<code>port</code>
         *
         * @param cameraController the command source
         * @param host the name or ip address of the server host machine
         * @param port the port on which the server is listening
         */
        Client(const CameraController& cameraController,
          const std::string host, unsigned short port);

        /**
         * packs commands from <code>cameraController</code> into
         * <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param cameraController the controller whose commands are to be packed
         */
        static void packCommands(Commands& commands,
          const CameraController& cameraController);

    };

};

}

#endif
