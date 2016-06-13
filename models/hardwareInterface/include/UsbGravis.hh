/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbGravis.cpp}
 */

#ifndef _USB_GRAVIS_HH_
#define _USB_GRAVIS_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/Gravis.hh"

namespace idf {

/**
 * USB Gravis hand controller
 *
 * @author Derek Bankieris
 */
class UsbGravis : public UsbDevice, public Gravis {

    public:

    /** @copydoc UsbChProPedals::UsbChProPedals */
    UsbGravis(int vendorID = 0x0428, int productID = 0x4001);

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
