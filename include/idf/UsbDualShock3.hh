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

#ifndef USB_DUAL_SHOCK_3_HH
#define USB_DUAL_SHOCK_3_HH

#include "idf/UsbDualShock.hh"
#include "idf/DualShock3.hh"

namespace idf {

/** USB Sony PlayStation DUALSHOCK3 SIXAXIS controller */
class UsbDualShock3 : public UsbDualShock, public DualShock3 {

    public:

    /** constructor */
    UsbDualShock3();

    void decode(const std::vector<unsigned char>& data);
    void sendCommand();

};

}

#endif
