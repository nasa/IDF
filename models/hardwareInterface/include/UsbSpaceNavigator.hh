/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(hardwareInterface/src/UsbSpaceNavigator.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbSpaceNavigator.cpp}
 */

#ifndef _USB_SPACE_NAVIGATOR_HH_
#define _USB_SPACE_NAVIGATOR_HH_

#include "hardwareInterface/include/UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"

namespace idf {

/**
 * USB SpaceNavigator hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceNavigator : public UsbSpaceBase, public SpaceNavigator {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbSpaceNavigator(int vendorID = 0x046D, int productID = 0xC628);

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
