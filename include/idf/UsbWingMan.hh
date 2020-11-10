/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbWingMan.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbWingMan.cpp}
 */

#ifndef USB_WING_MAN_HH
#define USB_WING_MAN_HH

#include "idf/UsbDevice.hh"
#include "idf/WingMan.hh"

namespace idf {

/** USB WingMan joystick */
class UsbWingMan : public UsbDevice, public virtual WingMan {

    public:

    /** constructor */
    UsbWingMan();

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbWingMan(const std::string& name, unsigned packetLength);

};

}

#endif
