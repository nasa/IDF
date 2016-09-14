/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSpaceNavigator.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSpaceNavigator.cpp}
 */

#ifndef USB_SPACE_NAVIGATOR_HH
#define USB_SPACE_NAVIGATOR_HH

#include "idf/UsbSpaceBase.hh"
#include "idf/SpaceNavigator.hh"

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
