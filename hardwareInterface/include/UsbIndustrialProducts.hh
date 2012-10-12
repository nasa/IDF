/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbIndustrialProducts.cpp))
 */

#ifndef _USB_INDUSTRIAL_PRODUCTS_HH_
#define _USB_INDUSTRIAL_PRODUCTS_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/IndustrialProducts.hh"

namespace hardware {

/**
 * represents a USB IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class UsbIndustrialProducts : public UsbDevice, public IndustrialProducts {

    public:

    /** constructor */
    UsbIndustrialProducts(int vendorID = 0x046D, int productID = 0xC212);

    void update();

    void printState();

};

}

#endif
