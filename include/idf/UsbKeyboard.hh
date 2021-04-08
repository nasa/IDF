/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbKeyboard.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbKeyboard.cpp}
 */

#ifndef USB_KEYBOARD_HH
#define USB_KEYBOARD_HH

#include "idf/UsbDevice.hh"
#include "idf/Keyboard.hh"

namespace idf {

/** USB Keyboard */
class UsbKeyboard : public UsbDevice, public Keyboard {

    public:

    /**
     * constructor
     *
     * @param vendor vendor ID
     * @param product product ID
     */
    UsbKeyboard(int vendor, int product, int interface = 0);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
