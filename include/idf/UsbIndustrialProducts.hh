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

#ifndef _USB_INDUSTRIAL_PRODUCTS_HH_
#define _USB_INDUSTRIAL_PRODUCTS_HH_

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
