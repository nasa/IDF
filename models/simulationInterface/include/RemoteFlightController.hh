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
     * a server which accepts and manages connections from multiple
     * {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public FlightController, public RemoteDeviceServer<Commands> {

        public:

        /**
         * constructs an instance which listens for connections on
         * <code>port</code>
         *
         * @param port the port over which to listen for connections
         */
        Server(unsigned short port = 0);

        /** destructor */
        virtual ~Server() {};

        /**
         * gets the roll value, normalized to [-1, 0, 1]
         *
         * @return the roll of all added flight controllers
         */
        virtual double getCommandedRoll() const;

        /**
         * gets the pitch value, normalized to [-1, 0, 1]
         *
         * @return the pitch of all added flight controllers
         */
        virtual double getCommandedPitch() const;

        /**
         * gets the yaw value, normalized to [-1, 0, 1]
         *
         * @return the yaw of all added flight controllers
         */
        virtual double getCommandedYaw() const;

        /**
         * gets the x value, normalized to [-1, 0, 1]
         *
         * @return the x of all added flight controllers
         */
        virtual double getCommandedX() const;

        /**
         * gets the y value, normalized to [-1, 0, 1]
         *
         * @return the y of all added flight controllers
         */
        virtual double getCommandedY() const;

        /**
         * gets the z value, normalized to [-1, 0, 1]
         *
         * @return the z of all added flight controllers
         */
        virtual double getCommandedZ() const;

        private:

        /**
         * unpacks the normalized <code>value</code>
         *
         * @param the normalized value
         */
        static double unpack(signed char value);

    };

    /**
     * transmits commands from a contained {@link FlightController} to a
     * <code>Server</code>
     *
     * @author Derek Bankieris
     */
    class Client {

        public:

        /** the flight controller whose commands are to be transmitted */
        const FlightController& flightController;

        /**
         * constructs an instance that transmits commands from
         * <code>flightController</code> to the <code>Server</code>
         * listening on <code>host</code>:<code>port</code>
         *
         * @param flightController the command source
         * @param host the name or ip address of the server host machine
         * @param port the port on which the server is listening
         */
        Client(const FlightController& flightController,
          const std::string host, unsigned short port);

        /** destructor */
        virtual ~Client();

        /**
         * packs <code>roll</code>, <code>pitch</code>, <code>yaw</code>,
         * <code>x</code>, <code>y</code>, and <code>z</code> into
         * <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param normalizedRoll the roll command normalized to [-1, 0, 1]
         * @param normalizedPitch the pitch command normalized to [-1, 0, 1]
         * @param normalizedYaw the yaw command normalized to [-1, 0, 1]
         * @param normalizedX the x command normalized to [-1, 0, 1]
         * @param normalizedY the y command normalized to [-1, 0, 1]
         * @param normalizedZ the z command normalized to [-1, 0, 1]
         */
        static void packCommands(Commands& commands,
          double normalizedRoll, double normalizedPitch, double normalizedYaw,
          double normalizedX, double normalizedY, double normalizedZ);

        /**
         * packs commands from <code>flightController</code> into
         * <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param flightController the controller whose commands are to be packed
         */
        static void packCommands(Commands& commands,
          const FlightController& flightController);

        /** sends the commands to the server */
        void transmit();

        /**
         * THIS FUNCTION SHOULD NOT BE CALLED
         * This class is not copy-assignable, but SWIG doesn't support embedded
         * classes, so this function must be public. It returns an INVALID
         * reference.
         * */
        Client& operator=(const Client&) {
            Client* error = NULL;
            return (Client&)*error;
        };

        protected:

        /** the socket */
        int socketHandle;

        /**
         * bounds <code>value</code> to [-1, 1]
         *
         * @param value the value to bound
         *
         * @return the bounded value
         */
        static double bound(double value);

    };

};

}

#endif
