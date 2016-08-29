/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDualShock4.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDualShock4.cpp}
 */

#ifndef _USB_DUAL_SHOCK_4_HH_
#define _USB_DUAL_SHOCK_4_HH_

#include "idf/UsbDualShock.hh"
#include "idf/DualShock4.hh"

namespace idf {

/**
 * USB Sony PlayStation DUALSHOCK4 SIXAXIS controller
 *
 * @author Derek Bankieris
 */
class UsbDualShock4 : public UsbDualShock, public DualShock4 {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbDualShock4(int vendorID = 0x054C, int productID = 0x05C4);

    void decode(const std::vector<unsigned char>& data);
    void sendCommand();

};

}

#endif
