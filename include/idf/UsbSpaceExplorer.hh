/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSpaceExplorer.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSpaceExplorer.cpp}
 */

#ifndef _USB_SPACE_EXPLORER_HH_
#define _USB_SPACE_EXPLORER_HH_

#include "idf/UsbSpaceBase.hh"
#include "idf/SpaceExplorer.hh"

namespace idf {

/**
 * USB SpaceExplorer hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceExplorer : public UsbSpaceBase, public SpaceExplorer {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbSpaceExplorer(int vendorID = 0x46D, int productID = 0xC627);

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
