/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDualShock3.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDualShock3.cpp}
 */

#ifndef _USB_DUAL_SHOCK_3_HH_
#define _USB_DUAL_SHOCK_3_HH_

#include "idf/UsbDualShock.hh"
#include "idf/DualShock3.hh"

namespace idf {

/**
 * USB Sony PlayStation DUALSHOCK3 SIXAXIS controller
 *
 * @author Derek Bankieris
 */
class UsbDualShock3 : public UsbDualShock, public DualShock3 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbDualShock3(int vendorID = 0x054C, int productID = 0x0268);

    void decode(const std::vector<unsigned char>& data);
    void sendCommand();

};

}

#endif
