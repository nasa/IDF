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

#ifndef USB_DUAL_SHOCK_4_HH
#define USB_DUAL_SHOCK_4_HH

#include "idf/UsbDualShock.hh"
#include "idf/DualShock4.hh"

namespace idf {

/** USB Sony PlayStation DUALSHOCK4 SIXAXIS controller */
class UsbDualShock4 : public UsbDualShock, public DualShock4 {

    public:

    /** constructor */
    UsbDualShock4();

    void decode(const std::vector<unsigned char>& data);
    void sendCommand();

};

}

#endif
