/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbGravis.cpp))
 */

#ifndef _USB_GRAVIS_HH_
#define _USB_GRAVIS_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/Gravis.hh"

namespace idf {

/**
 * represents a USB Gravis hand controller
 *
 * @author Derek Bankieris
 */
class UsbGravis : public UsbDevice, public Gravis {

    public:

    /** constructor */
    UsbGravis(int vendorID = 0x0428, int productID = 0x4001);

    void update();

};

}

#endif
