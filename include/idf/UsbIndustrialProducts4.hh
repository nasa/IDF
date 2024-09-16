/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbIndustrialProducts4.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbIndustrialProducts4.cpp}
 */

#ifndef USB_INDUSTRIAL_PRODUCTS4_HH
#define USB_INDUSTRIAL_PRODUCTS4_HH

#include "idf/UsbDevice.hh"
#include "idf/IndustrialProducts4.hh"

namespace idf {

/** USB IndustrialProducts joystick. Implementation of APEM HJRMCSAUYGLEA Hand Controller */
class UsbIndustrialProducts4 : public UsbDevice, public IndustrialProducts4 {

    public:

    /** constructor */
    UsbIndustrialProducts4();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
