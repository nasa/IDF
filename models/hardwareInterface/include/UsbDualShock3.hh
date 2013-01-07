/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbDualShock3.cpp))
 */

#ifndef _USB_DUAL_SHOCK_3_HH_
#define _USB_DUAL_SHOCK_3_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/DualShock3.hh"

namespace idf {

/**
 * represents a USB Sony DUALSHOCK3 SIXAXIS hand controller
 *
 * @author Derek Bankieris
 */
class UsbDualShock3 : public UsbDevice, public DualShock3 {

    public:

    /** constructor */
    UsbDualShock3(int vendorID = 0x054C, int productID = 0x0268);

    void open();

    void update();

    void sendCommand();

};

}

#endif
