#include "idf/RemoteCameraController.hh"

namespace idf {

CameraControllerServer::CameraControllerServer(unsigned short port) :
    Server<CameraControllerCommands>(port) {}

double CameraControllerServer::getCommandedPan() const {
    return accumulateClientValues(&CameraControllerCommands::pan, std::plus<double>());
}

double CameraControllerServer::getCommandedTilt() const {
    return accumulateClientValues(&CameraControllerCommands::tilt, std::plus<double>());
}

double CameraControllerServer::getCommandedSpin() const {
    return accumulateClientValues(&CameraControllerCommands::spin, std::plus<double>());
}

double CameraControllerServer::getCommandedZoom() const {
    return accumulateClientValues(&CameraControllerCommands::zoom, std::plus<double>());
}

CameraControllerClient::CameraControllerClient(const CameraController& flightController,
  const std::string& hostName, unsigned short hostPort) :
    Client<CameraController, CameraControllerCommands>(flightController, hostName, hostPort) {}

void CameraControllerClient::packCommands(CameraControllerCommands& commands) {
    commands.pan = pack(source.getPan());
    commands.tilt = pack(source.getTilt());
    commands.spin = pack(source.getSpin());
    commands.zoom = pack(source.getZoom());
}

}
