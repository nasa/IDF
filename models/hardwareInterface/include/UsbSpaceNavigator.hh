/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceNavigator.cpp))
 */

#ifndef _USB_SPACE_NAVIGATOR_HH_
#define _USB_SPACE_NAVIGATOR_HH_

#include "UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"

namespace idf {

/**
 * represents a USB SpaceNavigator hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceNavigator : public UsbSpaceBase, public SpaceNavigator {

    public:

    /** constructor */
    UsbSpaceNavigator(int vendorID = 0x046D, int productID = 0xC628);

    protected:

    /**
     * processes the button data and sets the appropriate inputs
     *
     * @param buttonData the raw button data
     */
    void processButtons(unsigned char* buttonData);

};

}

#endif
