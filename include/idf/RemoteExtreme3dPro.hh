/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteExtreme3dPro.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/RemoteExtreme3dPro.cpp}
 */

#ifndef REMOTE_EXTREME_3D_PRO_HH
#define REMOTE_EXTREME_3D_PRO_HH

#include "idf/Extreme3dPro.hh"
#include "idf/Server.hh"
#include "idf/Client.hh"

namespace idf {

struct Extreme3dProCommands {
    signed char forwardBackwardPivot;
    signed char leftRightPivot;
    signed char twist;
    signed char trigger;
    signed char button2;
    signed char button3;
    signed char button4;
    signed char button5;
    signed char button6;
    signed char button7;
    signed char button8;
    signed char button9;
    signed char button10;
    signed char button11;
    signed char button12;
    signed char hatNorth;
    signed char hatNorthEast;
    signed char hatEast;
    signed char hatSouthEast;
    signed char hatSouth;
    signed char hatSouthWest;
    signed char hatWest;
    signed char hatNorthWest;
    signed char slider;
};

/**
 * accepts and manages connections from multiple {@link Extreme3dProClient}s
 *
 * @author Derek Bankieris
 */
class Extreme3dProServer : public Extreme3dPro, public Server<Extreme3dProCommands> {

    public:

    /** @copydoc Server::Server */
    Extreme3dProServer(unsigned short port = 0);

    void update();

};

/**
 * transmits commands from a contained Extreme3dPro to a Server
 *
 * @author Derek Bankieris
 */
class Extreme3dProClient : public Client<Extreme3dPro, Extreme3dProCommands> {

    public:

    /** @copydoc Client::Client */
    Extreme3dProClient(const Extreme3dPro& commandSource, const std::string& host, unsigned short port);

    void packCommands(Extreme3dProCommands& commands);

};

}

#endif
