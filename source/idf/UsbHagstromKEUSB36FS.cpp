#include "idf/UsbHagstromKEUSB36FS.hh"

namespace idf {

UsbHagstromKEUSB36FS::UsbHagstromKEUSB36FS() :
    UsbDevice("Hagstrom KE-USB36FS", 64) {}

void UsbHagstromKEUSB36FS::decode(const std::vector<unsigned char>& data) {
    for (std::vector<SingleInput*>::iterator i = inputs.begin(); i != inputs.end(); ++i) {
        (*i)->setValue(0);
    }

    for (std::vector<unsigned char>::const_iterator i = data.begin() + 2; i != data.end(); ++i) {
        std::map<int, SingleInput*>::iterator entry = map.find(*i);
        if (entry != map.end()) {
            entry->second->setValue(1);
        }
    }
}

}
