#include "idf/RemoteSpaceNavigator.hh"
#include "idf/Utils.hh"
#include "idf/IOException.hh"
#include <exception>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <iomanip>
#include <iomanip>

namespace idf {

RemoteSpaceNavigatorServer::RemoteSpaceNavigatorServer(unsigned short listenPort) :
    RemoteDeviceServer<RemoteSpaceNavigatorCommands>(listenPort) {}

// TODO: fix, only accepts last clients commands
void RemoteSpaceNavigatorServer::update() {
    RemoteDeviceServer<RemoteSpaceNavigatorCommands>::update();

    if (clients.empty()) {
        forwardBackwardPivot.setValue(forwardBackwardPivot.getNeutralValue());
        leftRightPivot.setValue(leftRightPivot.getNeutralValue());
        twist.setValue(twist.getNeutralValue());
        forwardBackwardTranslation.setValue(forwardBackwardTranslation.getNeutralValue());
        leftRightTranslation.setValue(leftRightTranslation.getNeutralValue());
        upDownTranslation.setValue(upDownTranslation.getNeutralValue());
        leftButton.setValue(leftButton.getNeutralValue());
        rightButton.setValue(rightButton.getNeutralValue());
    }
    else {
        for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); ++i) {
            forwardBackwardPivot.setValue(i->commands.forwardBackwardPivot);
            leftRightPivot.setValue(i->commands.leftRightPivot);
            twist.setValue(i->commands.twist);
            forwardBackwardTranslation.setValue(i->commands.forwardBackwardTranslation);
            leftRightTranslation.setValue(i->commands.leftRightTranslation);
            upDownTranslation.setValue(i->commands.upDownTranslation);
            leftButton.setValue(i->commands.leftButton);
            rightButton.setValue(i->commands.rightButton);
        }
    }
}

RemoteSpaceNavigatorClient::RemoteSpaceNavigatorClient(const SpaceNavigator& spaceNavigator,
  std::string hostName, unsigned short hostPort) :
    RemoteDeviceClient<SpaceNavigator, RemoteSpaceNavigatorCommands>(spaceNavigator, hostName, hostPort) {}

void RemoteSpaceNavigatorClient::packCommands(RemoteSpaceNavigatorCommands& commands,
  const SpaceNavigator& spaceNavigator) {
    commands.forwardBackwardPivot = spaceNavigator.forwardBackwardPivot.getValue();
    commands.leftRightPivot = spaceNavigator.leftRightPivot.getValue();
    commands.twist = spaceNavigator.twist.getValue();
    commands.forwardBackwardTranslation = spaceNavigator.forwardBackwardTranslation.getValue();
    commands.leftRightTranslation = spaceNavigator.leftRightTranslation.getValue();
    commands.upDownTranslation = spaceNavigator.upDownTranslation.getValue();
    commands.leftButton = spaceNavigator.leftButton.getValue();
    commands.rightButton = spaceNavigator.rightButton.getValue();
}

}
