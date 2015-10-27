/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbDualShock3.cpp))
 */

#ifndef _USB_DUAL_SHOCK_3_HH_
#define _USB_DUAL_SHOCK_3_HH_

#include "hardwareInterface/include/UsbDualShock.hh"
#include "inputAbstraction/include/DualShock3.hh"

namespace idf {

/**
 * represents a USB Sony PlayStation DUALSHOCK3 SIXAXIS controller
 *
 * @author Derek Bankieris
 */
class UsbDualShock3 : public idf::UsbDualShock, public DualShock3 {

    public:

    /** constructor */
    UsbDualShock3(int vendorID = 0x054C, int productID = 0x0268);

    void update();
    void sendCommand();

};

}

#endif
