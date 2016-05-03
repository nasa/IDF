#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "hardwareInterface/include/UsbDevice.hh"
#include "hardwareInterface/include/UsbChProPedals.hh"
#include "hardwareInterface/include/UsbDualShock3.hh"
#include "hardwareInterface/include/UsbDualShock4.hh"
#include "hardwareInterface/include/UsbExtreme3dPro.hh"
#include "hardwareInterface/include/UsbGravis.hh"
#include "hardwareInterface/include/UsbIndustrialProducts.hh"
#include "hardwareInterface/include/UsbSaitek.hh"
#include "hardwareInterface/include/UsbSpaceExplorer.hh"
#include "hardwareInterface/include/UsbSpaceMouse.hh"
#include "hardwareInterface/include/UsbSpaceNavigator.hh"
#include "hardwareInterface/include/UsbWingMan.hh"
#include "hardwareInterface/include/UsbXBox.hh"

namespace configurator {

static int index = -1;

bool notConnected(idf::UsbDevice* device) {
    return !device->isConnected();
}

void printIndex(const std::string& text) {
    std::cout << std::setw(2) << ++index << "  " << text << std::endl;
}

void run() {
    idf::UsbChProPedals chProPedals;
    idf::UsbDualShock3 dualShock3;
    idf::UsbDualShock4 dualShock4;
    idf::UsbExtreme3dPro extreme3dPro;
    idf::UsbGravis gravis;
    idf::UsbIndustrialProducts industrialProducts;
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
    std::cout << std::endl;

    int selection = -1;
    while (selection < 0 || selection > index) {
        std::cout << "Select a device to configure: ";
        std::cin >> selection;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (selection > 0) {
        idf::UsbDevice& device =  *devices[selection - 1];
        device.open();
        std::cout << std::endl << "Configuring: " << device.name << std::endl << std::endl;
        device.configure();
    }
    else {
        std::cout << "Not yet implemented" << std::endl;
    }
}

}

int main(int argc, char **args) {
    configurator::run();
    return 0;
}
