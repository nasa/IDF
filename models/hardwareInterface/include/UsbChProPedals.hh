/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbChProPedals.cpp))
 */

#ifndef _USB_CH_PRO_PEDALS_HH_
#define _USB_CH_PRO_PEDALS_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/ChProPedals.hh"

namespace idf {

/**
 * represents a USB Ch Pro Pedals input device
 *
 * @author Derek Bankieris
 */
class UsbChProPedals : public UsbDevice, public ChProPedals {

    public:

    /** constructor */
    UsbChProPedals(int vendorID = 0x068E, int productID = 0x00F2);

    void update();

};

}

#endif
