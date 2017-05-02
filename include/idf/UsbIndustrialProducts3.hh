/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbIndustrialProducts3.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbIndustrialProducts3.cpp}
 */

#ifndef USB_INDUSTRIAL_PRODUCTS3_HH
#define USB_INDUSTRIAL_PRODUCTS3_HH

#include "idf/UsbDevice.hh"
#include "idf/IndustrialProducts3.hh"

namespace idf {

/**
 * USB IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class UsbIndustrialProducts3 : public UsbDevice, public IndustrialProducts3 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbIndustrialProducts3(int vendorID = 0x068E, int productID = 0x0026);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
