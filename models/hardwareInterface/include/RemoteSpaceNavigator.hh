/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/RemoteSpaceNavigator.cpp))
 */

#ifndef _REMOTE_SPACE_NAVIGATOR_HH_
#define _REMOTE_SPACE_NAVIGATOR_HH_

#include "inputAbstraction/include/SpaceNavigator.hh"
#include "hardwareInterface/include/RemoteDeviceServer.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"

namespace idf {

//class RemoteSpaceNavigator {

//    public:

    /** structure used to serialze commands */
    /** TODO: fix
     * WARNING: This is, in general, a TERRIBLE approach. Doubles are not safe for
     * network transmission. They're used here because this class is part of an
     * emergency (limited-time) development effort.
     */
    struct RemoteSpaceNavigatorCommands {
        double forwardBackwardPivot;
        double leftRightPivot;
        double twist;
        double forwardBackwardTranslation;
        double leftRightTranslation;
        double upDownTranslation;
        double leftButton;
        double rightButton;
    };

#ifdef SWIG
%template (RemoteDeviceServer_RemoteSpaceNavigator) RemoteDeviceServer<RemoteSpaceNavigatorCommands>;
#endif
    /**
     * a server which accepts and manages connections from multiple
     * {@link Client}s
     *
     * @author Derek Bankieris
     */
    class RemoteSpaceNavigatorServer : public SpaceNavigator, public RemoteDeviceServer<RemoteSpaceNavigatorCommands> {

        public:

        /**
         * constructs an instance which listens for connections on
         * <code>port</code>
         *
         * @param port the port over which to listen for connections
         */
        RemoteSpaceNavigatorServer(unsigned short port = 0);

        void update();

    };

#ifdef SWIG
class RemoteSpaceNavigatorClient;
%template (RemoteDeviceClient_RemoteSpaceNavigator) RemoteDeviceClient<SpaceNavigator, RemoteSpaceNavigatorCommands, RemoteSpaceNavigatorClient>;
#endif
    /**
     * transmits commands from a contained {@link SpaceNavigator} to a
     * <code>RemoteSpaceNavigatorServer</code>
     *
     * @author Derek Bankieris
     */
    class RemoteSpaceNavigatorClient : public RemoteDeviceClient<SpaceNavigator, RemoteSpaceNavigatorCommands, RemoteSpaceNavigatorClient> {

        public:

        /**
         * constructs an instance that transmits commands from
         * <code>spaceNavigator</code> to the <code>RemoteSpaceNavigatorServer</code>
         * listening on <code>host</code>:<code>port</code>
         *
         * @param spaceNavigator the command source
         * @param host the name or ip address of the server host machine
         * @param port the port on which the server is listening
         */
        RemoteSpaceNavigatorClient(const SpaceNavigator& spaceNavigator,
          const std::string host, unsigned short port);

        /**
         * packs commands from <code>spaceNavigator</code> into
         * <code>commands</code>
         *
         * @param commands the structure into which the commands are packed
         * @param spaceNavigator the controller whose commands are to be packed
         */
        static void packCommands(RemoteSpaceNavigatorCommands& commands,
          const SpaceNavigator& spaceNavigator);

        private:
        void operator=(const RemoteSpaceNavigatorClient&);

    };

//};

}

#endif
