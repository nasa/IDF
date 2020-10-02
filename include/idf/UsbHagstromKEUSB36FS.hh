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

/** USB HagstromKEUSB36FS board */
class UsbHagstromKEUSB36FS : public UsbDevice, public HagstromKEUSB36 {

    public:

    /** constructor */
    UsbHagstromKEUSB36FS();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
