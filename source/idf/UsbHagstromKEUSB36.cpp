#include "idf/UsbHagstromKEUSB36.hh"

namespace idf {

UsbHagstromKEUSB36::UsbHagstromKEUSB36(int vendorID, int productID) :
    UsbDevice("Hagstrom KE-USB36", vendorID, productID, 8) {}

void UsbHagstromKEUSB36::decode(const std::vector<unsigned char>& data) {
    input1.setValue(0);
    input2.setValue(0);
    input3.setValue(0);
    input4.setValue(0);
    input5.setValue(0);
    input6.setValue(0);
    input7.setValue(0);
    input8.setValue(0);
    input9.setValue(0);
    input10.setValue(0);
    input11.setValue(0);
    input12.setValue(0);
    input13.setValue(0);
    input14.setValue(0);
    input15.setValue(0);
    input16.setValue(0);
    input17.setValue(0);
    input18.setValue(0);
    input19.setValue(0);
    input20.setValue(0);
    input21.setValue(0);
    input22.setValue(0);
    input23.setValue(0);
    input24.setValue(0);
    input25.setValue(0);
    input26.setValue(0);
    input27.setValue(0);
    input28.setValue(0);
    input29.setValue(0);
    input30.setValue(0);
    input31.setValue(0);
    input32.setValue(0);
    input33.setValue(0);
    input34.setValue(0);
    input35.setValue(0);
    input36.setValue(0);

    /**
     * Each input is represented as an individual byte, with support for up to
     * six simultaneous inputs. If only one input is active, it will be in byte
     * two. If two inputs are simultaneously active, the second will be in byte
     * three. This pattern repeats up to byte seven. If less than six inputs
     * are simultaneously active, the trailing bytes will be zero. If more than
     * six inputs are simultenously active, ALL bytes will be one.
     */
    for (std::vector<unsigned char>::const_iterator i = data.begin() + 2; i != data.end(); ++i) {
        if (*i == 0 || *i == 1) {
            break;
        }

        std::map<int, SingleInput*>::iterator entry = map.find(*i);
        if (entry != map.end()) {
            entry->second->setValue(1);
        }
    }
}

}
