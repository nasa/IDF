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

/** USB IndustrialProducts joystick */
class UsbIndustrialProducts2 : public UsbDevice, public IndustrialProducts2 {

    public:

    /** constructor */
    UsbIndustrialProducts2();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
