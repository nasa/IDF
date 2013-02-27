#include "RemoteFlightController.hh"
#include "hardwareInterface/include/IOException.hh"
#include <iostream>
#include <sstream>
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
    return result;
}

double RemoteFlightController::Server::getCommandedPitch() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.pitch);
    }
    return result;
}

double RemoteFlightController::Server::getCommandedYaw() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.yaw);
    }
    return result;
}

double RemoteFlightController::Server::getCommandedX() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.x);
    }
    return result;
}

double RemoteFlightController::Server::getCommandedY() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.y);
    }
    return result;
}

double RemoteFlightController::Server::getCommandedZ() const {
    double result = 0;
    for (std::vector<class Client>::const_iterator i = clients.begin(); i != clients.end(); ++i) {
        result += unpack(i->commands.z);
    }
    return result;
}

double RemoteFlightController::Server::unpack(signed char value) {
    return value / serializationFactor;
}

RemoteFlightController::Client::Client(const FlightController& controller,
  std::string host, unsigned short port) :
    flightController(controller) {

    std::stringstream ss;
    ss << port;

    // Get server connection information.
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *results;
    if (getaddrinfo(host.c_str(), ss.str().c_str(), &hints, &results)) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to resolve host address: " << strerror(errno);
        throw IOException(oss.str());
    }

    // Establish first available connection.
    struct addrinfo *currentHost;
    for (currentHost = results; currentHost != NULL; currentHost = currentHost->ai_next) {
        if ((socketHandle = socket(currentHost->ai_family,
          currentHost->ai_socktype, currentHost->ai_protocol)) == -1) {
            continue;
        }

        if (connect(socketHandle, currentHost->ai_addr, currentHost->ai_addrlen) == 0) {
            std::cout << __FILE__ << ":" << __LINE__
                      << " Connected to " << host << ":" << port << std::endl;
            break;
        }

        close(socketHandle);
    }

    freeaddrinfo(results);

    if (currentHost == NULL) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to connect to " << host << ":" << port << ": " << strerror(errno);
        throw IOException(oss.str());
    }
}

RemoteFlightController::Client::~Client() {
    close(socketHandle);
}

void RemoteFlightController::Client::packCommands(Commands& commands,
  double normalizaedRoll, double normalizaedPitch, double normalizaedYaw,
  double normalizaedX, double normalizaedY, double normalizedZ) {

    commands.roll = (signed char)(bound(normalizaedRoll) *
      Server::serializationFactor);

    commands.pitch = (signed char)(bound(normalizaedPitch) *
      Server::serializationFactor);

    commands.yaw = (signed char)(bound(normalizaedYaw) *
      Server::serializationFactor);

    commands.x = (signed char)(bound(normalizaedX) *
      Server::serializationFactor);

    commands.y = (signed char)(bound(normalizaedY) *
      Server::serializationFactor);

    commands.z = (signed char)(bound(normalizedZ) *
      Server::serializationFactor);
}

void RemoteFlightController::Client::packCommands(Commands& commands,
  const FlightController& controller) {
    packCommands(commands, controller.getRoll(), controller.getPitch(),
      controller.getYaw(), controller.getX(), controller.getY(), controller.getZ());
}

void RemoteFlightController::Client::transmit() {
    Commands commands;
    packCommands(commands, flightController);

    if (write(socketHandle, &commands, sizeof(commands)) == -1) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to write: " << strerror(errno);
        throw IOException(oss.str());
    }
}

double RemoteFlightController::Client::bound(double value) {
    return value > 1 ? 1 : (value < -1 ? -1 : value);
}
