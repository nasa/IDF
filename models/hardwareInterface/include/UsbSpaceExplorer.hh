/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbSpaceExplorer.cpp}
 */

#ifndef _USB_SPACE_EXPLORER_HH_
#define _USB_SPACE_EXPLORER_HH_

#include "hardwareInterface/include/UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"

namespace idf {

/**
 * represents a USB SpaceExplorer hand controller
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
