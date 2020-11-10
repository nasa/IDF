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

/** USB Mad Catz joystick */
class UsbMadCatz : public UsbDevice, public virtual MadCatz {

    public:

    /** constructor */
    UsbMadCatz();

    virtual void decode(const std::vector<unsigned char>& data);

};

}

#endif
