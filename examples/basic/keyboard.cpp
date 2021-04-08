#include <iostream>
#include <unistd.h>
#include "idf/UsbKeyboard.hh"

int main(int, char**) {
    idf::UsbKeyboard keyboard(0x413C, 0x2101);

    while (true) {
        keyboard.update();
        std::cout << "-------------------\n" << keyboard.getActiveDescription();
        usleep(100E3);
    }

    return 0;
}
