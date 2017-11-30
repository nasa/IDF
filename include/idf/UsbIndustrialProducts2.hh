/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbIndustrialProducts2.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbIndustrialProducts2.cpp}
 */

#ifndef USB_INDUSTRIAL_PRODUCTS2_HH
#define USB_INDUSTRIAL_PRODUCTS2_HH

#include "idf/UsbDevice.hh"
#include "idf/IndustrialProducts2.hh"

namespace idf {

/**
 * USB IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class UsbIndustrialProducts2 : public UsbDevice, public IndustrialProducts2 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbIndustrialProducts2(int vendorID = 0x068E, int productID = 0x0019);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
