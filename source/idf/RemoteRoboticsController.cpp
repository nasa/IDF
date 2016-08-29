#include "idf/RemoteRoboticsController.hh"
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

namespace idf {

RemoteRoboticsController::Server::Server(unsigned short listenPort) :
    RemoteDeviceServer<Commands>(listenPort) {}

double RemoteRoboticsController::Server::getCommandedRoll() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.roll);
    }
    return bound(result);
}

double RemoteRoboticsController::Server::getCommandedPitch() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.pitch);
    }
    return bound(result);
}

double RemoteRoboticsController::Server::getCommandedYaw() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.yaw);
    }
    return bound(result);
}

double RemoteRoboticsController::Server::getCommandedX() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.x);
    }
    return bound(result);
}

double RemoteRoboticsController::Server::getCommandedY() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.y);
    }
    return bound(result);
}

double RemoteRoboticsController::Server::getCommandedZ() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.z);
    }
    return bound(result);
}

bool RemoteRoboticsController::Server::getCommandedTrigger() const {
    bool result = false;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result  = result || i->commands.trigger;
    }
    return result;
}

bool RemoteRoboticsController::Server::getCommandedRateMode() const {
    bool result = false;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result  = result || i->commands.rateMode;
    }
    return result;
}

RemoteRoboticsController::Client::Client(const RoboticsController& roboticsController,
  std::string hostName, unsigned short hostPort) :
    RemoteDeviceClient<RoboticsController, Commands>(roboticsController, hostName, hostPort) {}

void RemoteRoboticsController::Client::packCommands(Commands& commands) {
    packCommands(commands, controller);
}

void RemoteRoboticsController::Client::packCommands(Commands& commands,
  const RoboticsController& roboticsController) {
    commands.roll = pack(roboticsController.getRoll());
    commands.pitch = pack(roboticsController.getPitch());
    commands.yaw = pack(roboticsController.getYaw());
    commands.x = pack(roboticsController.getX());
    commands.y = pack(roboticsController.getY());
    commands.z = pack(roboticsController.getZ());
    commands.trigger = roboticsController.getTrigger();
    commands.rateMode = roboticsController.getRateMode();
}

}
