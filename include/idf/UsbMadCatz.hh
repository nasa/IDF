/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbMadCatz.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbMadCatz.cpp}
 */

#ifndef USB_MAD_CATZ_HH
#define USB_MAD_CATZ_HH

#include "idf/UsbDevice.hh"
#include "idf/MadCatz.hh"

namespace idf {

/**
 * USB MadCatz hand controller
 *
 * @author Derek Bankieris
 */
class UsbMadCatz : public UsbDevice, public virtual MadCatz {

    public:

    /** @copydoc UsbSpaceBase::UsbSpaceBase */
    UsbMadCatz(int vendorID = 0x0738, int productID = 0x1302, const std::string& name = "Mad Catz");

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbMadCatz(int vendorID, int productID, const std::string& name, unsigned packetLength);

    private:

    /** this class is not copy-assignable */
    void operator=(const UsbMadCatz&);

};

}

#endif
