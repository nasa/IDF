/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbHagstromKEUSB36FS.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbHagstromKEUSB36FS.cpp}
 */

#ifndef USB_HAGSTROM_KEUSB36FS_HH
#define USB_HAGSTROM_KEUSB36FS_HH

#include "idf/UsbDevice.hh"
#include "idf/HagstromKEUSB36.hh"

namespace idf {

// USB HagstromKEUSB36FS input device
class UsbHagstromKEUSB36FS : public UsbDevice, public HagstromKEUSB36 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbHagstromKEUSB36FS(int vendorID = 0x03EB, int productID = 0x3650);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
