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

#ifndef REMOTE_CAMERA_CONTROLLER_HH
#define REMOTE_CAMERA_CONTROLLER_HH

#include "idf/CameraController.hh"
#include "idf/Server.hh"
#include "idf/Client.hh"

namespace idf {

/** structure used to serialze commands */
struct CameraControllerCommands {

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
 * accepts and manages connections from multiple {@link CameraControllerClient}s
 *
 * @author Derek Bankieris
 */
class CameraControllerServer : public CameraController, public Server<CameraControllerCommands> {

    public:

    /** @copydoc Server::Server */
    CameraControllerServer(unsigned short port = 0);

    double getCommandedPan() const;
    double getCommandedTilt() const;
    double getCommandedSpin() const;
    double getCommandedZoom() const;

};

/**
 * transmits commands from a contained CameraController to a Server
 *
 * @author Derek Bankieris
 */
class CameraControllerClient : public Client<CameraController, CameraControllerCommands> {

    public:

    /** @copydoc Client::Client */
    CameraControllerClient(const CameraController& commandSource, const std::string& host, unsigned short port);

    void packCommands(CameraControllerCommands& commands);

};

}

#endif
