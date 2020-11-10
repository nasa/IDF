/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbExtreme3dPro.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbExtreme3dPro.cpp}
 */

#ifndef USB_EXTREME_3D_PRO_HH
#define USB_EXTREME_3D_PRO_HH

#include "idf/UsbWingMan.hh"
#include "idf/Extreme3dPro.hh"

namespace idf {

/** USB Extreme3dPro joystick */
class UsbExtreme3dPro : public UsbWingMan, public Extreme3dPro {

    public:

    /** constructor */
    UsbExtreme3dPro();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
