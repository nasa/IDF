/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceNavigator.cpp))
 */

#ifndef _USB_SPACE_NAVIGATOR_HH_
#define _USB_SPACE_NAVIGATOR_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"

namespace idf {

/**
 * represents a USB SpaceNavigator hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceNavigator : public UsbDevice, public SpaceNavigator {

    public:

    /** constructor */
    UsbSpaceNavigator(int vendorID = 0x046D, int productID = 0xC628);

    void update();

};

}

#endif
