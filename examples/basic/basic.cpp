#include <iomanip>
#include <iostream>
#include <unistd.h>
#include "idf/UsbHagstromKEUSB36FS.hh"

int main(int, char**) {
    idf::UsbHagstromKEUSB36FS hagstrom;
    const std::vector<idf::SingleInput*>& inputs = hagstrom.getInputs();

    while (true) {
        hagstrom.update();
        std::cout << std::showpos << std::fixed << std::setprecision(0);
        for (std::vector<idf::SingleInput*>::const_iterator i = inputs.begin(); i != inputs.end(); ++i) {
            std::cout << (*i)->getNormalizedValue()  << " ";
        }
        std::cout << '\n';
        usleep(1E6);
    }

    return 0;
}
