/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbChProPedals.cpp}
 */

#ifndef _USB_CH_PRO_PEDALS_HH_
#define _USB_CH_PRO_PEDALS_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/ChProPedals.hh"

namespace idf {

/**
 * USB Ch Pro Pedals input device
 *
 * @author Derek Bankieris
 */
class UsbChProPedals : public UsbDevice, public ChProPedals {

    public:

    /**
     * constructs a new instance whose open() will look for a USB
     * device with the @a vendorID and @a productID
     *
     * @param vendorID the target USB device's vendorID
     * @param productID the target USB device's productID
     */
    UsbChProPedals(int vendorID = 0x068E, int productID = 0x00F2);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
