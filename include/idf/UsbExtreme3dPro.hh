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

#ifndef _USB_EXTREME_3D_PRO_HH_
#define _USB_EXTREME_3D_PRO_HH_

#include "idf/UsbWingMan.hh"
#include "idf/Extreme3dPro.hh"

namespace idf {

/**
 * USB Extreme3dPro hand controller
 *
 * @author Derek Bankieris
 */
class UsbExtreme3dPro : public UsbWingMan, public Extreme3dPro {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbExtreme3dPro(int vendorID = 0x046D, int productID = 0xC215);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
