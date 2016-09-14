/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbXBox.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbXBox.cpp}
 */

#ifndef USB_XBOX_HH
#define USB_XBOX_HH

#include "idf/UsbDevice.hh"
#include "idf/XBox.hh"

namespace idf {

/**
 * USB XBox hand controller
 *
 * @author Derek Bankieris
 */
class UsbXBox : public UsbDevice, public XBox {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbXBox(int vendorID = 0x045E, int productID = 0x028E);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
