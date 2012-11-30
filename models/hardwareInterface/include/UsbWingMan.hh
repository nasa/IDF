/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbWingMan.cpp))
 */

#ifndef _USB_WING_MAN_HH_
#define _USB_WING_MAN_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/WingMan.hh"

namespace idf {

/**
 * represents a USB WingMan hand controller
 *
 * @author Derek Bankieris
 */
class UsbWingMan : public UsbDevice, public WingMan {

    public:

    /** constructor */
    UsbWingMan(int vendorID = 0x046D, int productID = 0xC212);

    void update();

};

}

#endif
