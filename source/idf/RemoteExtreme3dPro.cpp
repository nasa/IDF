#include "idf/RemoteExtreme3dPro.hh"

namespace idf {

Extreme3dProServer::Extreme3dProServer(unsigned short port) :
    Server<Extreme3dProCommands>(port) {}

void Extreme3dProServer::update() {
    Server<Extreme3dProCommands>::update();

    forwardBackwardPivot.setValue(accumulateClientValues(&Extreme3dProCommands::forwardBackwardPivot, std::plus<double>()));
    leftRightPivot.setValue(accumulateClientValues(&Extreme3dProCommands::leftRightPivot, std::plus<double>()));
    twist.setValue(accumulateClientValues(&Extreme3dProCommands::twist, std::plus<double>()));
    trigger.setValue(accumulateClientValues(&Extreme3dProCommands::trigger, std::plus<double>()));
    button2.setValue(accumulateClientValues(&Extreme3dProCommands::button2, std::plus<double>()));
    button3.setValue(accumulateClientValues(&Extreme3dProCommands::button3, std::plus<double>()));
    button4.setValue(accumulateClientValues(&Extreme3dProCommands::button4, std::plus<double>()));
    button5.setValue(accumulateClientValues(&Extreme3dProCommands::button5, std::plus<double>()));
    button6.setValue(accumulateClientValues(&Extreme3dProCommands::button6, std::plus<double>()));
    button7.setValue(accumulateClientValues(&Extreme3dProCommands::button7, std::plus<double>()));
    button8.setValue(accumulateClientValues(&Extreme3dProCommands::button8, std::plus<double>()));
    button9.setValue(accumulateClientValues(&Extreme3dProCommands::button9, std::plus<double>()));
    button10.setValue(accumulateClientValues(&Extreme3dProCommands::button10, std::plus<double>()));
    button11.setValue(accumulateClientValues(&Extreme3dProCommands::button11, std::plus<double>()));
    button12.setValue(accumulateClientValues(&Extreme3dProCommands::button12, std::plus<double>()));
    hatNorth.setValue(accumulateClientValues(&Extreme3dProCommands::hatNorth, std::plus<double>()));
    hatNorthEast.setValue(accumulateClientValues(&Extreme3dProCommands::hatNorthEast, std::plus<double>()));
    hatEast.setValue(accumulateClientValues(&Extreme3dProCommands::hatEast, std::plus<double>()));
    hatSouthEast.setValue(accumulateClientValues(&Extreme3dProCommands::hatSouthEast, std::plus<double>()));
    hatSouth.setValue(accumulateClientValues(&Extreme3dProCommands::hatSouth, std::plus<double>()));
    hatSouthWest.setValue(accumulateClientValues(&Extreme3dProCommands::hatSouthWest, std::plus<double>()));
    hatWest.setValue(accumulateClientValues(&Extreme3dProCommands::hatWest, std::plus<double>()));
    hatNorthWest.setValue(accumulateClientValues(&Extreme3dProCommands::hatNorthWest, std::plus<double>()));
    slider.setValue(accumulateClientValues(&Extreme3dProCommands::slider, std::plus<double>()));
}

Extreme3dProClient::Extreme3dProClient(const Extreme3dPro& extreme3dPro,
  const std::string& hostName, unsigned short hostPort) :
    Client<Extreme3dPro, Extreme3dProCommands>(extreme3dPro, hostName, hostPort) {}

void Extreme3dProClient::packCommands(Extreme3dProCommands& commands) {
    commands.forwardBackwardPivot = pack(source.forwardBackwardPivot.getValue());
    commands.leftRightPivot = pack(source.leftRightPivot.getValue());
    commands.twist = pack(source.twist.getValue());
    commands.trigger = pack(source.trigger.getValue());
    commands.button2 = pack(source.button2.getValue());
    commands.button3 = pack(source.button3.getValue());
    commands.button4 = pack(source.button4.getValue());
    commands.button5 = pack(source.button5.getValue());
    commands.button6 = pack(source.button6.getValue());
    commands.button7 = pack(source.button7.getValue());
    commands.button8 = pack(source.button8.getValue());
    commands.button9 = pack(source.button9.getValue());
    commands.button10 = pack(source.button10.getValue());
    commands.button11 = pack(source.button11.getValue());
    commands.button12 = pack(source.button12.getValue());
    commands.hatNorth = pack(source.hatNorth.getValue());
    commands.hatNorthEast = pack(source.hatNorthEast.getValue());
    commands.hatEast = pack(source.hatEast.getValue());
    commands.hatSouthEast = pack(source.hatSouthEast.getValue());
    commands.hatSouth = pack(source.hatSouth.getValue());
    commands.hatSouthWest = pack(source.hatSouthWest.getValue());
    commands.hatWest = pack(source.hatWest.getValue());
    commands.hatNorthWest = pack(source.hatNorthWest.getValue());
    commands.slider = pack(source.slider.getValue());
}

}
