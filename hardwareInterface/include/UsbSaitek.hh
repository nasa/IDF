/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSaitek.cpp))
 */

#ifndef _USB_GRAVIS_HH_
#define _USB_GRAVIS_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/Saitek.hh"

namespace idf {

/**
 * represents a USB Saitek Pro Flight Foot Pedals input device
 *
 * @author Derek Bankieris
 */
class UsbSaitek : public UsbDevice, public Saitek {

    public:

    /** constructor */
    UsbSaitek(int vendorID = 0x06A3, int productID = 0x0763);

    void update();

};

}

#endif
