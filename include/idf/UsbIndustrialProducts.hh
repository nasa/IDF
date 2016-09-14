/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbIndustrialProducts.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbIndustrialProducts.cpp}
 */

#ifndef USB_INDUSTRIAL_PRODUCTS_HH
#define USB_INDUSTRIAL_PRODUCTS_HH

#include "idf/UsbDevice.hh"
#include "idf/IndustrialProducts2.hh"

namespace idf {

/**
 * USB IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class UsbIndustrialProducts : public UsbDevice, public IndustrialProducts2 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbIndustrialProducts(int vendorID = 0x068E, int productID = 0x002E);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
