/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(simulationInterface/src/RemoteRoboticsController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{simulationInterface/src/RemoteRoboticsController.cpp}
 */

#ifndef _REMOTE_ROBOTICS_CONTROLLER_HH_
#define _REMOTE_ROBOTICS_CONTROLLER_HH_

#include "simulationInterface/include/RoboticsController.hh"
#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"

namespace idf {

/** provides the infrastructure for establishing a remote RoboticsController */
class RemoteRoboticsController {

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

        /** trigger command */
        bool trigger;

        /** rate mode command */
        bool rateMode;

    };

    /**
     * accepts and manages connections from multiple {@link Client}s
     *
     * @author Derek Bankieris
     */
    class Server : public RoboticsController, public RemoteDeviceServer<Commands> {

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
         * @return the roll of all added robotics controllers
         */
        double getCommandedRoll() const;

        /**
         * gets the pitch value, normalized to [-1, 0, 1]
         *
         * @return the pitch of all added robotics controllers
         */
        double getCommandedPitch() const;

        /**
         * gets the yaw value, normalized to [-1, 0, 1]
         *
         * @return the yaw of all added robotics controllers
         */
        double getCommandedYaw() const;

        /**
         * gets the x value, normalized to [-1, 0, 1]
         *
         * @return the x of all added robotics controllers
         */
        double getCommandedX() const;

        /**
         * gets the y value, normalized to [-1, 0, 1]
         *
         * @return the y of all added robotics controllers
         */
        double getCommandedY() const;

        /**
         * gets the z value, normalized to [-1, 0, 1]
         *
         * @return the z of all added robotics controllers
         */
        double getCommandedZ() const;

        /**
         * gets the trigger value, which is the logical OR of all added controllers' trigger values
         *
         * @return the trigger of all added robotics controllers
         */
        bool getCommandedTrigger() const;

        /**
         * gets the rate mode value, which is the logical OR of all added controllers' rate mode values
         *
         * @return the rate mode of all added robotics controllers
         */
        bool getCommandedRateMode() const;

    };

    /**
     * transmits commands from a contained RoboticsController to a Server
     *
     * @author Derek Bankieris
     */
    class Client : public RemoteDeviceClient<RoboticsController, Commands> {

        public:

        /** @copydoc RemoteDeviceClient::RemoteDeviceClient */
        Client(const RoboticsController& sourceController, const std::string hostName, unsigned short hostPort);

        /** @copydoc RemoteCameraController::Client::packCommands */
        void static packCommands(Commands& commands, const RoboticsController& controller);

        void packCommands(Commands& commands);

    };
    #endif

};

}

#endif
