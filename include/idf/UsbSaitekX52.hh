/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSaitekX52.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSaitekX52.cpp}
 */

#ifndef USB_SAITEK_X52_HH
#define USB_SAITEK_X52_HH

#include "idf/UsbDevice.hh"
#include "idf/SaitekX52.hh"

namespace idf {

/** USB SaitekX52 Pro Flight X52 Flight System */
class UsbSaitekX52 : public UsbDevice, public SaitekX52 {

    public:

    /** constructor */
    UsbSaitekX52();

    void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbSaitekX52(const std::string& name, unsigned packetLength);
};

}

#endif
