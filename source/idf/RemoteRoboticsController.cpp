#include "idf/RemoteRoboticsController.hh"

namespace idf {

RoboticsControllerServer::RoboticsControllerServer(unsigned short port) :
    Server<RoboticsControllerCommands>(port) {}

double RoboticsControllerServer::getCommandedRoll() const {
    return accumulateClientValues(&RoboticsControllerCommands::roll, std::plus<double>());
}

double RoboticsControllerServer::getCommandedPitch() const {
    return accumulateClientValues(&RoboticsControllerCommands::pitch, std::plus<double>());
}

double RoboticsControllerServer::getCommandedYaw() const {
    return accumulateClientValues(&RoboticsControllerCommands::yaw, std::plus<double>());
}

double RoboticsControllerServer::getCommandedX() const {
    return accumulateClientValues(&RoboticsControllerCommands::x, std::plus<double>());
}

double RoboticsControllerServer::getCommandedY() const {
    return accumulateClientValues(&RoboticsControllerCommands::y, std::plus<double>());
}

double RoboticsControllerServer::getCommandedZ() const {
    return accumulateClientValues(&RoboticsControllerCommands::z, std::plus<double>());
}

bool RoboticsControllerServer::getCommandedTrigger() const {
    return accumulateClientValues(&RoboticsControllerCommands::trigger, std::logical_or<bool>());
}

bool RoboticsControllerServer::getCommandedRateMode() const {
    return accumulateClientValues(&RoboticsControllerCommands::rateMode, std::logical_or<bool>());
}

RoboticsControllerClient::RoboticsControllerClient(const RoboticsController& roboticsController,
  const std::string& hostName, unsigned short hostPort) :
    Client<RoboticsController, RoboticsControllerCommands>(roboticsController, hostName, hostPort) {}

void RoboticsControllerClient::packCommands(RoboticsControllerCommands& commands) {
    commands.roll = pack(source.getRoll());
    commands.pitch = pack(source.getPitch());
    commands.yaw = pack(source.getYaw());
    commands.x = pack(source.getX());
    commands.y = pack(source.getY());
    commands.z = pack(source.getZ());
    commands.trigger = source.getTrigger();
    commands.rateMode = source.getRateMode();
}

}
