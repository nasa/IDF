/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/RemoteFlightController.cpp))
 */

#ifndef _REMOTE_FLIGHT_CONTROLLER_HH_
#define _REMOTE_FLIGHT_CONTROLLER_HH_

#include "FlightController.hh"
#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"

namespace idf {

class RemoteFlightController {

    public:

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
     * a server which accepts and manages connections from multiple {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public FlightController, public RemoteDeviceServer<Commands> {

        public:

        /**
         * constructs an instance which listens for connections on <code>port</code>
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
     * transmits commands from a contained {@link FlightController} to a <code>Server</code>
     *
     * @author Derek Bankieris
     */
    class Client : public RemoteDeviceClient<FlightController, Commands, Client> {

        public:

        /**
         * constructs an instance that transmits commands from <code>flightController</code> to the <code>Server</code>
         * listening on <code>host</code>:<code>port</code>
         *
         * @param flightController the command source
         * @param host the name or ip address of the server host machine
         * @param port the port on which the server is listening
         */
        Client(const FlightController& flightController, const std::string host, unsigned short port);

        /**
         * packs commands from <code>flightController</code> into <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param flightController the controller whose commands are to be packed
         */
        static void packCommands(Commands& commands, const FlightController& flightController);

    };

};

}

#endif
