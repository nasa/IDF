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
class UsbWingMan : public UsbDevice, public virtual WingMan {

    public:

    /** constructor */
    UsbWingMan(int vendorID = 0x046D, int productID = 0xC212);

    void update();

    protected:

    /** number of bytes per status message */
    const int byteCount;

    /** constructor */
    UsbWingMan(int vendorID, int productID, int byteCount);

    /**
     * decodes the raw data and fills in input values
     *
     * @param data the raw data from the device
     */
    virtual void processData(unsigned char *data);

    private:

    /** this class is not copy-assignable */
    void operator=(const UsbWingMan&);

};

}

#endif
