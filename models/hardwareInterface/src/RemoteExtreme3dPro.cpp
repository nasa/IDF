#include "RemoteExtreme3dPro.hh"
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

RemoteExtreme3dProServer::RemoteExtreme3dProServer(unsigned short listenPort) :
    RemoteDeviceServer<RemoteExtreme3dProCommands>(listenPort) {}

// TODO: fix, only accepts last client's commands
void RemoteExtreme3dProServer::update() {
    RemoteDeviceServer<RemoteExtreme3dProCommands>::update();

    if (clients.empty()) {
        forwardBackwardPivot.setValue(forwardBackwardPivot.getNeutralValue());
        leftRightPivot.setValue(leftRightPivot.getNeutralValue());
        twist.setValue(twist.getNeutralValue());
        trigger.setValue(trigger.getNeutralValue());
        button2.setValue(button2.getNeutralValue());
        button3.setValue(button3.getNeutralValue());
        button4.setValue(button4.getNeutralValue());
        button5.setValue(button5.getNeutralValue());
        button6.setValue(button6.getNeutralValue());
        button7.setValue(button7.getNeutralValue());
        button8.setValue(button8.getNeutralValue());
        button9.setValue(button9.getNeutralValue());
        button10.setValue(button10.getNeutralValue());
        button11.setValue(button11.getNeutralValue());
        button12.setValue(button12.getNeutralValue());
        hatNorth.setValue(hatNorth.getNeutralValue());
        hatNorthEast.setValue(hatNorthEast.getNeutralValue());
        hatEast.setValue(hatEast.getNeutralValue());
        hatSouthEast.setValue(hatSouthEast.getNeutralValue());
        hatSouth.setValue(hatSouth.getNeutralValue());
        hatSouthWest.setValue(hatSouthWest.getNeutralValue());
        hatWest.setValue(hatWest.getNeutralValue());
        hatNorthWest.setValue(hatNorthWest.getNeutralValue());
        slider.setValue(slider.getNeutralValue());
    }
    else {
        for (std::vector<Client>::iterator i = clients.begin(); i != clients.end(); ++i) {
            forwardBackwardPivot.setValue(i->commands.forwardBackwardPivot);
            leftRightPivot.setValue(i->commands.leftRightPivot);
            twist.setValue(i->commands.twist);
            trigger.setValue(i->commands.trigger);
            button2.setValue(i->commands.button2);
            button3.setValue(i->commands.button3);
            button4.setValue(i->commands.button4);
            button5.setValue(i->commands.button5);
            button6.setValue(i->commands.button6);
            button7.setValue(i->commands.button7);
            button8.setValue(i->commands.button8);
            button9.setValue(i->commands.button9);
            button10.setValue(i->commands.button10);
            button11.setValue(i->commands.button11);
            button12.setValue(i->commands.button12);
            hatNorth.setValue(i->commands.hatNorth);
            hatNorthEast.setValue(i->commands.hatNorthEast);
            hatEast.setValue(i->commands.hatEast);
            hatSouthEast.setValue(i->commands.hatSouthEast);
            hatSouth.setValue(i->commands.hatSouth);
            hatSouthWest.setValue(i->commands.hatSouthWest);
            hatWest.setValue(i->commands.hatWest);
            hatNorthWest.setValue(i->commands.hatNorthWest);
            slider.setValue(i->commands.slider);
        }
    }
}

RemoteExtreme3dProClient::RemoteExtreme3dProClient(const Extreme3dPro& extreme3dPro,
  std::string hostName, unsigned short hostPort) :
    RemoteDeviceClient<Extreme3dPro, RemoteExtreme3dProCommands, RemoteExtreme3dProClient>(extreme3dPro, hostName, hostPort) {}

void RemoteExtreme3dProClient::packCommands(RemoteExtreme3dProCommands& commands,
  const Extreme3dPro& extreme3dPro) {
    commands.forwardBackwardPivot = extreme3dPro.forwardBackwardPivot.getValue();
    commands.leftRightPivot = extreme3dPro.leftRightPivot.getValue();
    commands.twist = extreme3dPro.twist.getValue();
    commands.trigger = extreme3dPro.trigger.getValue();
    commands.button2 = extreme3dPro.button2.getValue();
    commands.button3 = extreme3dPro.button3.getValue();
    commands.button4 = extreme3dPro.button4.getValue();
    commands.button5 = extreme3dPro.button5.getValue();
    commands.button6 = extreme3dPro.button6.getValue();
    commands.button7 = extreme3dPro.button7.getValue();
    commands.button8 = extreme3dPro.button8.getValue();
    commands.button9 = extreme3dPro.button9.getValue();
    commands.button10 = extreme3dPro.button10.getValue();
    commands.button11 = extreme3dPro.button11.getValue();
    commands.button12 = extreme3dPro.button12.getValue();
    commands.hatNorth = extreme3dPro.hatNorth.getValue();
    commands.hatNorthEast = extreme3dPro.hatNorthEast.getValue();
    commands.hatEast = extreme3dPro.hatEast.getValue();
    commands.hatSouthEast = extreme3dPro.hatSouthEast.getValue();
    commands.hatSouth = extreme3dPro.hatSouth.getValue();
    commands.hatSouthWest = extreme3dPro.hatSouthWest.getValue();
    commands.hatWest = extreme3dPro.hatWest.getValue();
    commands.hatNorthWest = extreme3dPro.hatNorthWest.getValue();
    commands.slider = extreme3dPro.slider.getValue();
}
