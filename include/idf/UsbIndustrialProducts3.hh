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

/** USB IndustrialProducts joystick */
class UsbIndustrialProducts3 : public UsbDevice, public IndustrialProducts3 {

    public:

    /** constructor */
    UsbIndustrialProducts3();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
