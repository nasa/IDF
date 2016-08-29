/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteFlightController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RemoteFlightController.cpp}
 */

#ifndef _REMOTE_FLIGHT_CONTROLLER_HH_
#define _REMOTE_FLIGHT_CONTROLLER_HH_

#include "idf/FlightController.hh"
#include "idf/RemoteDeviceServer.hh"
#include "idf/RemoteDeviceClient.hh"

namespace idf {

/** provides the infrastructure for establishing a remote FlightController */
class RemoteFlightController {

    public:

    #ifndef SWIG
    /** structure used to serialze commands */
    struct Commands {

        /** serialized commanded roll */
        signed char roll;

        /** serialized commanded pitch */
        signed char pitch;

        /** serialized commanded yaw */
        signed char yaw;

        /** serialized commanded x */
        signed char x;

        /** serialized commanded y */
        signed char y;

        /** serialized commanded z */
        signed char z;

    };

    /**
     * accepts and manages connections from multiple {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public FlightController, public RemoteDeviceServer<Commands> {

        public:

        /**
         * constructs an instance which listens for connections on @a port
         *
         * @param port the port over which to listen for connections
         */
        Server(unsigned short port = 0);

        /**
         * gets the roll value, normalized to [-1, 0, 1]
         *
         * @return the roll of all added flight controllers
         */
        double getCommandedRoll() const;

        /**
         * gets the pitch value, normalized to [-1, 0, 1]
         *
         * @return the pitch of all added flight controllers
         */
        double getCommandedPitch() const;

        /**
         * gets the yaw value, normalized to [-1, 0, 1]
         *
         * @return the yaw of all added flight controllers
         */
        double getCommandedYaw() const;

        /**
         * gets the x value, normalized to [-1, 0, 1]
         *
         * @return the x of all added flight controllers
         */
        double getCommandedX() const;

        /**
         * gets the y value, normalized to [-1, 0, 1]
         *
         * @return the y of all added flight controllers
         */
        double getCommandedY() const;

        /**
         * gets the z value, normalized to [-1, 0, 1]
         *
         * @return the z of all added flight controllers
         */
        double getCommandedZ() const;

    };

    /**
     * transmits commands from a contained FlightController to a Server
     *
     * @author Derek Bankieris
     */
    class Client : public RemoteDeviceClient<FlightController, Commands> {

        public:

        /** @copydoc RemoteDeviceClient::RemoteDeviceClient */
        Client(const FlightController& sourceController, const std::string hostName, unsigned short hostPort);

        /** @copydoc RemoteCameraController::Client::packCommands */
        void static packCommands(Commands& commands, const FlightController& controller);

        void packCommands(Commands& commands);

    };
    #endif

};

}

#endif
