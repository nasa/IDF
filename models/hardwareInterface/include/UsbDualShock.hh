/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbDualShock.cpp}
 */

#ifndef _USB_DUAL_SHOCK_HH_
#define _USB_DUAL_SHOCK_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/DualShock.hh"

namespace idf {

/**
 * common aspects of all Sony PlayStation DUALSHOCK controllers
 *
 * @author Derek Bankieris
 */
class UsbDualShock : public UsbDevice, public virtual DualShock {

    public:

    /** @copydoc UsbDevice::UsbDevice */
    UsbDualShock(const std::string name, int vendorID, int productID, unsigned packetLength);

    /** destructor */
    virtual ~UsbDualShock() {};

    private:

    void operator=(const UsbDualShock&);

};

}

#endif
