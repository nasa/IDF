/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSaitekX56Throttle.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSaitekX56Throttle.cpp}
 */

#ifndef USB_SAITEK_X56_THROTTLE_HH
#define USB_SAITEK_X56_THROTTLE_HH

#include "idf/UsbDevice.hh"
#include "idf/SaitekX56Throttle.hh"

namespace idf {

/** USB Saitek Pro Flight X-56 Rhino Throttle */
class UsbSaitekX56Throttle : public UsbDevice, public virtual SaitekX56Throttle {

    public:

    /** constructor */
    UsbSaitekX56Throttle();

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbSaitekX56Throttle(const std::string& name, unsigned packetLength);

};

}

#endif