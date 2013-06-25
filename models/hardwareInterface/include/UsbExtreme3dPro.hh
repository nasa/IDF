/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbExtreme3dPro.cpp))
 */

#ifndef _USB_EXTREME_3D_PRO_HH_
#define _USB_EXTREME_3D_PRO_HH_

#include "UsbWingMan.hh"
#include "inputAbstraction/include/Extreme3dPro.hh"

namespace idf {

/**
 * represents a USB Extreme3dPro hand controller
 *
 * @author Derek Bankieris
 */
class UsbExtreme3dPro : public UsbWingMan, public Extreme3dPro {

    public:

    /** constructor */
    UsbExtreme3dPro(int vendorID = 0x046D, int productID = 0xC215);

    protected:

    /**
     * decodes the raw data and fills in input values
     *
     * @param data the raw data from the device
     */
    void processData(unsigned char *data);

};

}

#endif
