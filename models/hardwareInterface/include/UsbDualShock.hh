#ifndef _USB_DUAL_SHOCK_HH_
#define _USB_DUAL_SHOCK_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/DualShock.hh"

namespace idf {

/**
 * represents the common aspects of all Sony PlayStation DUALSHOCK controllers
 *
 * @author Derek Bankieris
 */
class UsbDualShock : public UsbDevice, public virtual DualShock {

    public:

    /** constructor */
    UsbDualShock(int vendorID, int productID) :
        UsbDevice(vendorID, productID) {}

    /** destructor */
    virtual ~UsbDualShock() {};

};

}

#endif
