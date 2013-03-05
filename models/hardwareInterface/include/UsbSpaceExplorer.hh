/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceExplorer.cpp))
 */

#ifndef _USB_SPACE_EXPLORER_HH_
#define _USB_SPACE_EXPLORER_HH_

#include "UsbSpaceBase.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"

namespace idf {

/**
 * represents a USB SpaceExplorer hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceExplorer : public UsbSpaceBase, public SpaceExplorer {

    public:

    /** constructor */
    UsbSpaceExplorer(int vendorID = 0x46D, int productID = 0xC627);

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
