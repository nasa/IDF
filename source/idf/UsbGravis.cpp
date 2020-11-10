#include "idf/UsbGravis.hh"

namespace idf {

UsbGravis::UsbGravis() :
    UsbDevice("Gravis", 4) {}

void UsbGravis::decode(const std::vector<unsigned char>& data) {
    directionalPadLeft.setValue(~data[0] & 1);
    directionalPadRight.setValue(data[0] >> 7);

    directionalPadUp.setValue(~data[1] & 1);
    directionalPadDown.setValue(data[1] >> 7);

    westButton.setValue(data[2] & 1);
    southButton.setValue(data[2] >> 1 & 1);
    eastButton.setValue(data[2] >> 2 & 1);
    northButton.setValue(data[2] >> 3 & 1);

    leftBumper1.setValue(data[2] >> 4 & 1);
    rightBumper1.setValue(data[2] >> 5 & 1);
    leftBumper2.setValue(data[2] >> 6 & 1);
    rightBumper2.setValue(data[2] >> 7 & 1);

    selectButton.setValue(data[3] & 1);
    startButton.setValue(data[3] >> 1 & 1);
}

}
