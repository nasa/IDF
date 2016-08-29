/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteCameraController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RemoteCameraController.cpp}
 */

#ifndef _REMOTE_CAMERA_CONTROLLER_HH_
#define _REMOTE_CAMERA_CONTROLLER_HH_

#include "idf/CameraController.hh"
#include "idf/RemoteDeviceServer.hh"
#include "idf/RemoteDeviceClient.hh"

namespace idf {

/** provides the infrastructure for establishing a remote CameraController */
class RemoteCameraController {

    public:

    #ifndef SWIG
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
     * accepts and manages connections from multiple {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public CameraController, public RemoteDeviceServer<Commands> {

        public:

        /**
         * constructs an instance which listens for connections on @a port
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
     * transmits commands from a contained CameraController to a Server
     *
     * @author Derek Bankieris
     */
    class Client : public RemoteDeviceClient<CameraController, Commands> {

        public:

        /** @copydoc RemoteDeviceClient::RemoteDeviceClient */
        Client(const CameraController& sourceController, const std::string hostName, unsigned short hostPort);

        /**
         * packs commands from @a controller into @a commands
         *
         * @param commands the structure into which the commands are packed
         * @param controller the controller whose commands are to be packed
         */
        void static packCommands(Commands& commands, const CameraController& controller);

        void packCommands(Commands& commands);

    };
    #endif

};

}

#endif
