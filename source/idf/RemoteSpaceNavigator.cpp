#include "idf/RemoteSpaceNavigator.hh"

namespace idf {

SpaceNavigatorServer::SpaceNavigatorServer(unsigned short port) :
    Server<SpaceNavigatorCommands>(port) {}

void SpaceNavigatorServer::update() {
    Server<SpaceNavigatorCommands>::update();

    forwardBackwardPivot.setValue(accumulateClientValues(&SpaceNavigatorCommands::forwardBackwardPivot, std::plus<double>()));
    leftRightPivot.setValue(accumulateClientValues(&SpaceNavigatorCommands::leftRightPivot, std::plus<double>()));
    twist.setValue(accumulateClientValues(&SpaceNavigatorCommands::twist, std::plus<double>()));
    forwardBackwardTranslation.setValue(accumulateClientValues(&SpaceNavigatorCommands::forwardBackwardTranslation, std::plus<double>()));
    leftRightTranslation.setValue(accumulateClientValues(&SpaceNavigatorCommands::leftRightTranslation, std::plus<double>()));
    upDownTranslation.setValue(accumulateClientValues(&SpaceNavigatorCommands::upDownTranslation, std::plus<double>()));
    leftButton.setValue(accumulateClientValues(&SpaceNavigatorCommands::leftButton, std::plus<double>()));
    rightButton.setValue(accumulateClientValues(&SpaceNavigatorCommands::rightButton, std::plus<double>()));
}

SpaceNavigatorClient::SpaceNavigatorClient(const SpaceNavigator& spaceNavigator,
  std::string hostName, unsigned short hostPort) :
    Client<SpaceNavigator, SpaceNavigatorCommands>(spaceNavigator, hostName, hostPort) {}

void SpaceNavigatorClient::packCommands(SpaceNavigatorCommands& commands) {
    commands.forwardBackwardPivot = pack(source.forwardBackwardPivot.getValue());
    commands.leftRightPivot = pack(source.leftRightPivot.getValue());
    commands.twist = pack(source.twist.getValue());
    commands.forwardBackwardTranslation = pack(source.forwardBackwardTranslation.getValue());
    commands.leftRightTranslation = pack(source.leftRightTranslation.getValue());
    commands.upDownTranslation = pack(source.upDownTranslation.getValue());
    commands.leftButton = pack(source.leftButton.getValue());
    commands.rightButton = pack(source.rightButton.getValue());
}

}
