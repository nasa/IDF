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

/** USB HagstromKEUSB36 board */
class UsbHagstromKEUSB36 : public UsbDevice, public HagstromKEUSB36 {

    public:

    /** constructor */
    UsbHagstromKEUSB36();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
