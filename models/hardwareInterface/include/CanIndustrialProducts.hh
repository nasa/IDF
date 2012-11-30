/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/CanIndustrialProducts.cpp))
 */

#ifndef _CAN_INDUSTRIAL_PRODUCTS_HH_
#define _CAN_INDUSTRIAL_PRODUCTS_HH_

#include "CanDevice.hh"
#include "inputAbstraction/include/IndustrialProducts.hh"

namespace idf {

/**
 * represents a CAN IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class CanIndustrialProducts : public CanDevice, public IndustrialProducts {

    public:

    /** constructor */
    CanIndustrialProducts(int networkID = 0, int baudrate = 1000);

    void update();

};

}

#endif
