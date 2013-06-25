#include "RemoteCameraController.hh"
#include "inputAbstraction/include/Utils.hh"
#include "hardwareInterface/include/RemoteDeviceClient.hh"
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

RemoteCameraController::Server::Server(unsigned short listenPort) :
    RemoteDeviceServer<Commands>(listenPort) {}

double RemoteCameraController::Server::getCommandedPan() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.pan);
    }
    return bound(result);
}

double RemoteCameraController::Server::getCommandedTilt() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.tilt);
    }
    return bound(result);
}

double RemoteCameraController::Server::getCommandedSpin() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.spin);
    }
    return bound(result);
}

double RemoteCameraController::Server::getCommandedZoom() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.zoom);
    }
    return bound(result);
}

RemoteCameraController::Client::Client(const CameraController& cameraController,
  std::string host, unsigned short port) :
    RemoteDeviceClient<CameraController, Commands, Client>(cameraController, host, port) {}

void RemoteCameraController::Client::packCommands(Commands& commands,
  const CameraController& cameraController) {
    commands.pan = pack(cameraController.getPan());
    commands.tilt = pack(cameraController.getTilt());
    commands.spin = pack(cameraController.getSpin());
    commands.zoom = pack(cameraController.getZoom());
}
