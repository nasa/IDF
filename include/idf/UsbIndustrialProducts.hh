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

/** USB IndustrialProducts joystick */
class UsbIndustrialProducts : public UsbDevice, public IndustrialProducts2 {

    public:

    /** constrctor */
    UsbIndustrialProducts();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
