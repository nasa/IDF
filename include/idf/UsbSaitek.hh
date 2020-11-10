/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSaitek.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSaitek.cpp}
 */

#ifndef USB_SAITEK_HH
#define USB_SAITEK_HH

#include "idf/UsbDevice.hh"
#include "idf/Saitek.hh"

namespace idf {

/** USB Saitek Pro Flight Rudder Pedals */
class UsbSaitek : public UsbDevice, public Saitek {

    public:

    /** constructor */
    UsbSaitek();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
