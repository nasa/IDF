/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbHagstromKEUSB36.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbHagstromKEUSB36.cpp}
 */

#ifndef USB_HAGSTROM_KEUSB36_HH
#define USB_HAGSTROM_KEUSB36_HH

#include "idf/UsbDevice.hh"
#include "idf/HagstromKEUSB36.hh"

namespace idf {

// USB HagstromKEUSB36 input device
class UsbHagstromKEUSB36 : public UsbDevice, public HagstromKEUSB36 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbHagstromKEUSB36(int vendorID = 0x04B4, int productID = 0x3648);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
