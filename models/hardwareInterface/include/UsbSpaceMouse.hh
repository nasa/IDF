/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(hardwareInterface/src/UsbSpaceMouse.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbSpaceMouse.cpp}
 */

#ifndef _USB_SPACE_MOUSE_HH_
#define _USB_SPACE_MOUSE_HH_

#include "hardwareInterface/include/UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceMouse.hh"

namespace idf {

/**
 * USB SpaceMouse hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceMouse : public UsbSpaceBase, public SpaceMouse {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbSpaceMouse(int vendorID = 0x46D, int productID = 0xC62B);

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
