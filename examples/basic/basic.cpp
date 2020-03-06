#include <iomanip>
#include <iostream>
#include <unistd.h>
#include "idf/UsbHagstromKEUSB36FS.hh"

int main(int, char**) {
    idf::UsbHagstromKEUSB36FS hagstrom;
    //hagstrom.setSerialNumber(L"11010149");
    //hagstrom.setPath("/dev/hidraw2");

    while (true) {
        hagstrom.update();

        std::cout << std::showpos << std::fixed << std::setprecision(0)
                  << hagstrom.input1.getNormalizedValue()  << " "
                  << hagstrom.input2.getNormalizedValue()  << " "
                  << hagstrom.input3.getNormalizedValue()  << " "
                  << hagstrom.input4.getNormalizedValue()  << " "
                  << hagstrom.input5.getNormalizedValue()  << " "
                  << hagstrom.input6.getNormalizedValue()  << " "
                  << hagstrom.input7.getNormalizedValue()  << " "
                  << hagstrom.input8.getNormalizedValue()  << " "
                  << hagstrom.input9.getNormalizedValue()  << " "
                  << hagstrom.input10.getNormalizedValue() << " "
                  << hagstrom.input11.getNormalizedValue() << " "
                  << hagstrom.input12.getNormalizedValue() << " "
                  << hagstrom.input13.getNormalizedValue() << " "
                  << hagstrom.input14.getNormalizedValue() << " "
                  << hagstrom.input15.getNormalizedValue() << " "
                  << hagstrom.input16.getNormalizedValue() << " "
                  << hagstrom.input17.getNormalizedValue() << " "
                  << hagstrom.input18.getNormalizedValue() << " "
                  << hagstrom.input19.getNormalizedValue() << " "
                  << hagstrom.input20.getNormalizedValue() << " "
                  << hagstrom.input21.getNormalizedValue() << " "
                  << hagstrom.input22.getNormalizedValue() << " "
                  << hagstrom.input23.getNormalizedValue() << " "
                  << hagstrom.input24.getNormalizedValue() << " "
                  << hagstrom.input25.getNormalizedValue() << " "
                  << hagstrom.input26.getNormalizedValue() << " "
                  << hagstrom.input27.getNormalizedValue() << " "
                  << hagstrom.input28.getNormalizedValue() << " "
                  << hagstrom.input29.getNormalizedValue() << " "
                  << hagstrom.input30.getNormalizedValue() << " "
                  << hagstrom.input31.getNormalizedValue() << " "
                  << hagstrom.input32.getNormalizedValue() << " "
                  << hagstrom.input33.getNormalizedValue() << " "
                  << hagstrom.input34.getNormalizedValue() << " "
                  << hagstrom.input35.getNormalizedValue() << " "
                  << hagstrom.input36.getNormalizedValue() << '\n';

        usleep(1E6);
    }

    return 0;
}
