/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSaitekX56Stick.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSaitekX56Stick.cpp}
 */

#ifndef USB_SAITEK_X56_STICK_HH
#define USB_SAITEK_X56_STICK_HH

#include "idf/UsbDevice.hh"
#include "idf/SaitekX56Stick.hh"

namespace idf {

/** USB Saitek Pro Flight X-56 Rhino Throttle */
class UsbSaitekX56Stick : public UsbDevice, public virtual SaitekX56Stick {

    public:

    /** constructor */
    UsbSaitekX56Stick();

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbSaitekX56Stick(const std::string& name, unsigned packetLength);

};

}

#endif