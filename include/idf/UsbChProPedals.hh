/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbChProPedals.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbChProPedals.cpp}
 */

#ifndef USB_CH_PRO_PEDALS_HH
#define USB_CH_PRO_PEDALS_HH

#include "idf/UsbDevice.hh"
#include "idf/ChProPedals.hh"

namespace idf {

/** USB Ch Pro Pedals foot pedals */
class UsbChProPedals : public UsbDevice, public ChProPedals {

    public:

    /** constructor */
    UsbChProPedals();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
