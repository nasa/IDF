/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbGravis.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbGravis.cpp}
 */

#ifndef USB_GRAVIS_HH
#define USB_GRAVIS_HH

#include "idf/UsbDevice.hh"
#include "idf/Gravis.hh"

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
