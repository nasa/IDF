/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbXBox.cpp))
 */

#ifndef _USB_XBOX_HH_
#define _USB_XBOX_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/XBox.hh"

namespace idf {

/**
 * represents a USB XBox hand controller
 *
 * @author Derek Bankieris
 */
class UsbXBox : public UsbDevice, public XBox {

    public:

    /** constructor */
    UsbXBox(int vendorID = 0x045E, int productID = 0x028E);

    void update();

};

}

#endif
