#include "hardwareInterface/include/InputDevice.hh"
#include "hardwareInterface/include/IOException.hh"
#include "inputAbstraction/include/SingleInput.hh"

#include <cerrno>
#include <cstring>
#include <limits>
#include <sys/select.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <sstream>

using namespace idf;

InputDevice::InputDevice(const std::string& id) :
    name(id),
    delay(0),
    enabled(true),
    mOpen(false) {}

bool InputDevice::isOpen() const {
    return mOpen;
}

void InputDevice::update() {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Device is not open.";
        throw IOException(oss.str());
    }
}

void InputDevice::configure() {
    configure(getConfigurables());
}

void InputDevice::configure(const std::vector<Configurable>& inputs) {
    if (inputs.empty()) {
        std::cout << "This device contains no configurable inputs." << std::endl;
        return;
    }

    update();
    size_t size = 0;
    for (std::vector<Configurable>::const_iterator i = inputs.begin(); i != inputs.end(); ++i) {
        size = std::max(size, i->name.length());
        double value = i->input->getValue();
        i->input->configure(value, value, value);
    }
    std::cout << "Press <Enter> when done" << std::endl << std::endl
              << std::setw(size) << "Input" << " Minimum Current Maximum" << std::endl;

    while (true) {
        update();
        for (std::vector<Configurable>::const_iterator i = inputs.begin(); i != inputs.end(); ++i) {
            SingleInput& input = *i->input;
            double value = input.getValue();
            input.configure(std::min(value, input.getMinimumValue()), std::max(value, input.getMaximumValue()), value);
            std::cout << std::setw(size) << i->name << " " << std::setw(7) << input.getMinimumValue() << " "
                      << std::setw(7) << value << " " << std::setw(7) << input.getMaximumValue() << std::endl;
        }

        fd_set set;
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        struct timeval timeout = {0, 0};
        if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) == -1) {
            throw IOException("Error while configuring: " + std::string(strerror(errno)));
        }
        else if (FD_ISSET(STDIN_FILENO, &set)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << std::endl << "Example input file configuration (note that the parameter order is min, max, neutral):"
                      << std::endl << std::endl << "device = trick.<call device constructor here>" << std::endl;
            for (std::vector<Configurable>::const_iterator i = inputs.begin(); i != inputs.end(); ++i) {
                SingleInput& input = *i->input;
                std::cout << "device." << i->variable << ".configure(" << input.getMinimumValue() << ", "
                          << input.getMaximumValue() << ", " << input.getNeutralValue() << ")" << std::endl;
            }
            return;
        }

        // a short sleep prevents the cursor from visually jumping all over the place
        usleep(100000);
        for (size_t i = 0; i < inputs.size(); ++i) {
            std::cout << "\x1b[A";
        }
    }
}
