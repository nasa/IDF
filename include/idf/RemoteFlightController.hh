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

#ifndef REMOTE_FLIGHT_CONTROLLER_HH
#define REMOTE_FLIGHT_CONTROLLER_HH

#include "idf/FlightController.hh"
#include "idf/Server.hh"
#include "idf/Client.hh"

namespace idf {

/** structure used to serialze commands */
struct FlightControllerCommands {

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

    /** comm command */
    bool comm;

    /** shutdown command */
    bool shutdown;

};

/**
 * To properly maintain inheritance, SWIG needs to wrap the template from which
 * this class derives. Only actual instances of a template can be wrapped, so
 * we must tell SWIG about this particular parameterization via %template.
 */
#ifdef SWIG
%template (Server_FlightControllerCommands) Server<FlightControllerCommands>;
#endif

/**
 * accepts and manages connections from multiple {@link FlightControllerClient}s
 *
 * @author Derek Bankieris
 */
class FlightControllerServer : public FlightController, public Server<FlightControllerCommands> {

    public:

    /** @copydoc Server::Server */
    FlightControllerServer(unsigned short port = 0);

    double getCommandedRoll() const;
    double getCommandedPitch() const;
    double getCommandedYaw() const;
    double getCommandedX() const;
    double getCommandedY() const;
    double getCommandedZ() const;
    bool getCommandedTrigger() const;
    bool getCommandedComm() const;
    bool getCommandedShutdown() const;

};

/**
 * To properly maintain inheritance, SWIG needs to wrap the template from which
 * this class derives. Only actual instances of a template can be wrapped, so
 * we must tell SWIG about this particular parameterization via %template.
 */
#ifdef SWIG
%template (Client_FlightController) Client<FlightController, FlightControllerCommands>;
#endif

/**
 * transmits commands from a contained FlightController to a Server
 *
 * @author Derek Bankieris
 */
class FlightControllerClient : public Client<FlightController, FlightControllerCommands> {

    public:

    /** @copydoc Client::Client */
    FlightControllerClient(const FlightController& commandSource, const std::string& host, unsigned short port);

    void packCommands(FlightControllerCommands& commands);

};

}

#endif
