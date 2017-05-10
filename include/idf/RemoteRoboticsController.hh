/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteRoboticsController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RemoteRoboticsController.cpp}
 */

#ifndef REMOTE_ROBOTICS_CONTROLLER_HH
#define REMOTE_ROBOTICS_CONTROLLER_HH

#include "idf/RoboticsController.hh"
#include "idf/Server.hh"
#include "idf/Client.hh"

namespace idf {

/** structure used to serialze commands */
struct RoboticsControllerCommands {

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
 * To properly maintain inheritance, SWIG needs to wrap the template from which
 * this class derives. Only actual instances of a template can be wrapped, so
 * we must tell SWIG about this particular parameterization via %template.
 */
#ifdef SWIG
%template (Server_RoboticsControllerCommands) Server<RoboticsControllerCommands>;
#endif

/**
 * accepts and manages connections from multiple {@link RoboticsControllerClient}s
 *
 * @author Derek Bankieris
 */
class RoboticsControllerServer : public RoboticsController, public Server<RoboticsControllerCommands> {

    public:

    /** @copydoc Server::Server */
    RoboticsControllerServer(unsigned short port = 0);

    double getCommandedRoll() const;
    double getCommandedPitch() const;
    double getCommandedYaw() const;
    double getCommandedX() const;
    double getCommandedY() const;
    double getCommandedZ() const;
    bool getCommandedTrigger() const;
    bool getCommandedRateMode() const;

};

/**
 * To properly maintain inheritance, SWIG needs to wrap the template from which
 * this class derives. Only actual instances of a template can be wrapped, so
 * we must tell SWIG about this particular parameterization via %template.
 */
#ifdef SWIG
%template (Client_RoboticsController) Client<RoboticsController, RoboticsControllerCommands>;
#endif

/**
 * transmits commands from a contained RoboticsController to a Server
 *
 * @author Derek Bankieris
 */
class RoboticsControllerClient : public Client<RoboticsController, RoboticsControllerCommands> {

    public:

    /** @copydoc Client::Client */
    RoboticsControllerClient(const RoboticsController& commandSource, const std::string& host, unsigned short port);

    void packCommands(RoboticsControllerCommands& commands);

};

}

#endif
