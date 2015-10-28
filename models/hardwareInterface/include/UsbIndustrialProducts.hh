/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbIndustrialProducts.cpp))
 */

#ifndef _USB_INDUSTRIAL_PRODUCTS_HH_
#define _USB_INDUSTRIAL_PRODUCTS_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/IndustrialProducts2.hh"

namespace idf {

/**
 * represents a USB IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class UsbIndustrialProducts : public UsbDevice, public IndustrialProducts2 {

    public:

    /** constructor */
    UsbIndustrialProducts(int vendorID = 0x068E, int productID = 0x002E);

    void update();

};

}

#endif
