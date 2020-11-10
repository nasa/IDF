/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/RemoteSpaceNavigator.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SpaceNavigator.cpp}
 */

#ifndef REMOTE_SPACE_NAVIGATOR_HH
#define REMOTE_SPACE_NAVIGATOR_HH

#include "idf/SpaceNavigator.hh"
#include "idf/Server.hh"
#include "idf/Client.hh"

namespace idf {

struct SpaceNavigatorCommands {
    signed char forwardBackwardPivot;
    signed char leftRightPivot;
    signed char twist;
    signed char forwardBackwardTranslation;
    signed char leftRightTranslation;
    signed char upDownTranslation;
    signed char leftButton;
    signed char rightButton;
};

/**
 * accepts and manages connections from multiple {@link SpaceNavigatorClient}s
 *
 * @author Derek Bankieris
 */
class SpaceNavigatorServer : public SpaceNavigator, public Server<SpaceNavigatorCommands> {

    public:

    /** @copydoc Server::Server */
    SpaceNavigatorServer(unsigned short port = 0);

    void update();

};

/**
 * transmits commands from a contained SpaceNavigator to a Server
 *
 * @author Derek Bankieris
 */
class SpaceNavigatorClient : public Client<SpaceNavigator, SpaceNavigatorCommands> {

    public:

    /** @copydoc Client::Client */
    SpaceNavigatorClient(const SpaceNavigator& commandSource, const std::string host, unsigned short port);

    void packCommands(SpaceNavigatorCommands& commands);

};

}

#endif
