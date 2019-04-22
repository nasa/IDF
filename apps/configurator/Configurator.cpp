#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "idf/SerialDevice.hh"
#include "idf/SerialThrustMaster.hh"
#include "idf/SerialThrustMaster2.hh"
#include "idf/UsbDevice.hh"
#include "idf/UsbChProPedals.hh"
#include "idf/UsbDualShock3.hh"
#include "idf/UsbDualShock4.hh"
#include "idf/UsbExtreme3dPro.hh"
#include "idf/UsbGravis.hh"
#include "idf/UsbIndustrialProducts.hh"
#include "idf/UsbIndustrialProducts2.hh"
#include "idf/UsbIndustrialProducts3.hh"
#include "idf/UsbMadCatz.hh"
#include "idf/UsbSaitek.hh"
#include "idf/UsbSpaceExplorer.hh"
#include "idf/UsbSpaceMouse.hh"
#include "idf/UsbSpaceNavigator.hh"
#include "idf/UsbWingMan.hh"
#include "idf/UsbXBox.hh"

namespace configurator {

static int index = -1;

bool notConnected(idf::UsbDevice* device) {
    return !device->isConnected();
}

void printIndex(const std::string& text) {
    std::cout << std::setw(2) << ++index << "  " << text << std::endl;
}

int getSelection() {
    int selection = -1;
    std::cout << std::endl;
    while (selection < 0 || selection > index) {
        std::cout << "Select a device to configure: ";
        std::cin >> selection;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return selection;
}

void configure(idf::InputDevice& device) {
    device.open();
    std::cout << std::endl << "Configuring: " << device.name << std::endl << std::endl;
    device.configure();
}

void run() {
    idf::UsbChProPedals chProPedals;
    idf::UsbDualShock3 dualShock3;
    idf::UsbDualShock4 dualShock4;
    idf::UsbExtreme3dPro extreme3dPro;
    idf::UsbGravis gravis;
    idf::UsbIndustrialProducts industrialProducts;
    idf::UsbIndustrialProducts2 industrialProducts2;
    idf::UsbIndustrialProducts3 industrialProducts3;
    idf::UsbMadCatz madcatz;
    idf::UsbSaitek saitek;
    idf::UsbSpaceExplorer spaceExplorer;
    idf::UsbSpaceMouse spaceMouse;
    idf::UsbSpaceNavigator spaceNavigator;
    idf::UsbWingMan wingMan;
    idf::UsbXBox xBox;

    std::vector<idf::UsbDevice*> devices;
    devices.push_back(&chProPedals);
    devices.push_back(&dualShock3);
    devices.push_back(&dualShock4);
    devices.push_back(&extreme3dPro);
    devices.push_back(&gravis);
    devices.push_back(&industrialProducts);
    devices.push_back(&industrialProducts2);
    devices.push_back(&industrialProducts3);
    devices.push_back(&madcatz);
    devices.push_back(&saitek);
    devices.push_back(&spaceExplorer);
    devices.push_back(&spaceMouse);
    devices.push_back(&spaceNavigator);
    devices.push_back(&wingMan);
    devices.push_back(&xBox);

    devices.erase(std::remove_if(devices.begin(), devices.end(), notConnected), devices.end());

    std::cout << std::endl << "NOTE: If running as non-root, you must have udev rules in place allowing access to usb devices." << std::endl << std::endl;

    printIndex("Serial Device");

    for (std::vector<idf::UsbDevice*>::size_type i = 0; i < devices.size(); ++i) {
        printIndex(devices[i]->name);
    }

    int selection = getSelection();
    if (selection == 0) {
        std::vector<idf::SerialDevice*> devices;
        idf::SerialThrustMaster shuttleThrustMaster;
        idf::SerialThrustMaster2 orionThrustMaster;
        devices.push_back(&shuttleThrustMaster);
        devices.push_back(&orionThrustMaster);
        index = -1;
        std::cout << std::endl;
        for (std::vector<idf::UsbDevice*>::size_type i = 0; i < devices.size(); ++i) {
            printIndex(devices[i]->name);
        }
        configure(*devices[getSelection()]);
    }
    else {
        configure(*devices[selection - 1]);
    }
}

}

int main(int argc, char **args) {
    configurator::run();
    return 0;
}
