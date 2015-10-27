/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceMouse.cpp))
 */

#ifndef _USB_SPACE_MOUSE_HH_
#define _USB_SPACE_MOUSE_HH_

#include "hardwareInterface/include/UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceMouse.hh"

namespace idf {

/**
 * represents a USB SpaceMouse hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceMouse : public UsbSpaceBase, public SpaceMouse {

    public:

    /** constructor */
    UsbSpaceMouse(int vendorID = 0x46D, int productID = 0xC62B);

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
