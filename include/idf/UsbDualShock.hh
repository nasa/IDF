/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDualShock.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDualShock.cpp}
 */

#ifndef USB_DUAL_SHOCK_HH
#define USB_DUAL_SHOCK_HH

#include "idf/UsbDevice.hh"
#include "idf/DualShock.hh"

namespace idf {

/** common aspects of all Sony PlayStation DUALSHOCK controllers */
class UsbDualShock : public UsbDevice, public virtual DualShock {

    public:

    /** @copydoc UsbDevice::UsbDevice */
    UsbDualShock(const std::string& name, unsigned packetLength);

    /** destructor */
    virtual ~UsbDualShock() {};

    private:

    void operator=(const UsbDualShock&);

};

}

#endif
