#include "idf/UsbKeyboard.hh"

namespace idf {

UsbKeyboard::UsbKeyboard(int vendor, int product, int interface) :
    UsbDevice("Keyboard", 8) {
    addIdentification(Identification(vendor, product, interface));
}

/**
 * Each input is represented as an individual byte, with support for up to six simultaneous inputs.
 * If only one input is active, it will be in byte two. If two inputs are simultaneously active, the
 * second will be in byte three. This pattern repeats up to byte seven. If less than six inputs are
 * simultaneously active, the trailing bytes will be zero. If more than six inputs are simultenously
 * active, bytes two through seven will be one.
 *
 * See https://www.usb.org/sites/default/files/hid1_11.pdf
 */
void UsbKeyboard::decode(const std::vector<unsigned char>& data) {

    // clear active keys
    for (std::vector<SingleInput*>::iterator it = active.begin(); it != active.end(); ++it) {
        (*it)->setValue(0);
    }
    active.clear();

    // update the modifiers
    leftCtrl.setValue(  data[0] & (1 << 0));
    leftShift.setValue( data[0] & (1 << 1));
    leftAlt.setValue(   data[0] & (1 << 2));
    leftGui.setValue(   data[0] & (1 << 3));
    rightCtrl.setValue( data[0] & (1 << 4));
    rightShift.setValue(data[0] & (1 << 5));
    rightAlt.setValue(  data[0] & (1 << 6));
    rightGui.setValue  (data[0] & (1 << 7));

    // set active keys
    for (std::vector<unsigned char>::const_iterator it = data.begin() + 2; it != data.end(); ++it) {
        if (*it < 4) {
            break;
        }

        std::map<unsigned char, SingleInput*>::iterator entry = map.find(*it);
        if (entry != map.end()) {
            entry->second->setValue(1);
            active.push_back(entry->second);
        }
    }
}

}
