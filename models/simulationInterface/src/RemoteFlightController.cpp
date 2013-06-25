#include "RemoteFlightController.hh"
#include "inputAbstraction/include/Utils.hh"
#include "hardwareInterface/include/IOException.hh"
#include <exception>
#include <cstring>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

using namespace idf;

RemoteFlightController::Server::Server(unsigned short listenPort) :
    RemoteDeviceServer<Commands>(listenPort) {}

double RemoteFlightController::Server::getCommandedRoll() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.roll);
    }
    return bound(result);
}

double RemoteFlightController::Server::getCommandedPitch() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.pitch);
    }
    return bound(result);
}

double RemoteFlightController::Server::getCommandedYaw() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.yaw);
    }
    return bound(result);
}

double RemoteFlightController::Server::getCommandedX() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.x);
    }
    return bound(result);
}

double RemoteFlightController::Server::getCommandedY() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.y);
    }
    return bound(result);
}

double RemoteFlightController::Server::getCommandedZ() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.z);
    }
    return bound(result);
}

RemoteFlightController::Client::Client(const FlightController& flightController,
  std::string host, unsigned short port) :
    RemoteDeviceClient<FlightController, Commands, Client>(flightController, host, port) {}

void RemoteFlightController::Client::packCommands(Commands& commands,
  const FlightController& flightController) {
    commands.roll = pack(flightController.getRoll());
    commands.pitch = pack(flightController.getPitch());
    commands.yaw = pack(flightController.getYaw());
    commands.x = pack(flightController.getX());
    commands.y = pack(flightController.getY());
    commands.z = pack(flightController.getZ());
}
