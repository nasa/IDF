/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbDualShock4.cpp))
 */

#ifndef _USB_DUAL_SHOCK_4_HH_
#define _USB_DUAL_SHOCK_4_HH_

#include "hardwareInterface/include/UsbDualShock.hh"
#include "inputAbstraction/include/DualShock4.hh"

namespace idf {

/**
 * represents a USB Sony PlayStation DUALSHOCK4 SIXAXIS controller
 *
 * @author Derek Bankieris
 */
class UsbDualShock4 : public UsbDualShock, public DualShock4 {

    public:

    /** constructor */
    UsbDualShock4(int vendorID = 0x054C, int productID = 0x05C4);

    void update();
    void sendCommand();

};

}

#endif
