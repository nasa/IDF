#include "idf/UsbHagstromKEUSB36.hh"

namespace idf {

UsbHagstromKEUSB36::UsbHagstromKEUSB36(int vendorID, int productID) :
    UsbDevice("Hagstrom KE-USB36", vendorID, productID, 8) {}

void UsbHagstromKEUSB36::decode(const std::vector<unsigned char>& data) {
    for (std::vector<SingleInput*>::iterator i = inputs.begin(); i != inputs.end(); ++i) {
        (*i)->setValue(0);
    }

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
