/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbXBox.cpp}
 */

#ifndef _USB_XBOX_HH_
#define _USB_XBOX_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/XBox.hh"

namespace idf {

/**
 * represents a USB XBox hand controller
 *
 * @author Derek Bankieris
 */
class UsbXBox : public UsbDevice, public XBox {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbXBox(int vendorID = 0x045E, int productID = 0x028E);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
