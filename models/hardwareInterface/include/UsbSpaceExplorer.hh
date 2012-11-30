/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceExplorer.cpp))
 */

#ifndef _USB_SPACE_EXPLORER_HH_
#define _USB_SPACE_EXPLORER_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"

namespace idf {

/**
 * represents a USB SpaceExplorer hand controller
 *
 * @author Derek Bankieris
 */
class UsbSpaceExplorer : public UsbDevice, public SpaceExplorer {

    public:

    /** constructor */
    UsbSpaceExplorer(int vendorID = 0x46D, int productID = 0xC627);

    void update();

};

}

#endif
