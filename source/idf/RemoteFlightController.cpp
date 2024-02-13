#include "idf/RemoteFlightController.hh"

namespace idf {

FlightControllerServer::FlightControllerServer(unsigned short port) :
    Server<FlightControllerCommands>(port) {}

double FlightControllerServer::getCommandedRoll() const {
    return accumulateClientValues(&FlightControllerCommands::roll, std::plus<double>());
}

double FlightControllerServer::getCommandedPitch() const {
    return accumulateClientValues(&FlightControllerCommands::pitch, std::plus<double>());
}

double FlightControllerServer::getCommandedYaw() const {
    return accumulateClientValues(&FlightControllerCommands::yaw, std::plus<double>());
}

double FlightControllerServer::getCommandedX() const {
    return accumulateClientValues(&FlightControllerCommands::x, std::plus<double>());
}

double FlightControllerServer::getCommandedY() const {
    return accumulateClientValues(&FlightControllerCommands::y, std::plus<double>());
}

double FlightControllerServer::getCommandedZ() const {
    return accumulateClientValues(&FlightControllerCommands::z, std::plus<double>());
}

bool FlightControllerServer::getCommandedTrigger() const {
    return accumulateClientValues(&FlightControllerCommands::trigger, std::logical_or<bool>());
}

bool FlightControllerServer::getCommandedComm() const {
    return accumulateClientValues(&FlightControllerCommands::comm, std::logical_or<bool>());
}

bool FlightControllerServer::getCommandedShutdown() const {
    return accumulateClientValues(&FlightControllerCommands::shutdown, std::logical_or<bool>());
}

FlightControllerClient::FlightControllerClient(const FlightController& flightController,
  const std::string& hostName, unsigned short hostPort) :
    Client<FlightController, FlightControllerCommands>(flightController, hostName, hostPort) {}

void FlightControllerClient::packCommands(FlightControllerCommands& commands) {
    commands.roll = pack(source.getRoll());
    commands.pitch = pack(source.getPitch());
    commands.yaw = pack(source.getYaw());
    commands.x = pack(source.getX());
    commands.y = pack(source.getY());
    commands.z = pack(source.getZ());
    commands.trigger = pack(source.getTrigger());
    commands.comm = pack(source.getComm());
    commands.shutdown = pack(source.getShutdown());
}

}
