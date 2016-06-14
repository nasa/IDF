/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(hardwareInterface/src/UsbWingMan.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/UsbWingMan.cpp}
 */

#ifndef _USB_WING_MAN_HH_
#define _USB_WING_MAN_HH_

#include "hardwareInterface/include/UsbDevice.hh"
#include "inputAbstraction/include/WingMan.hh"

namespace idf {

/**
 * USB WingMan hand controller
 *
 * @author Derek Bankieris
 */
class UsbWingMan : public UsbDevice, public virtual WingMan {

    public:

    /** @copydoc UsbSpaceBase::UsbSpaceBase */
    UsbWingMan(int vendorID = 0x046D, int productID = 0xC212, const std::string& name = "Wing Man");

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbWingMan(int vendorID, int productID, const std::string& name, unsigned packetLength);

    private:

    /** this class is not copy-assignable */
    void operator=(const UsbWingMan&);

};

}

#endif
