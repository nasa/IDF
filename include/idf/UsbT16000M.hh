/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbT16000M.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbT16000M.cpp}
 */

#ifndef USB_THRUST_MASTER_T16000M_FCS_HH
#define USB_THRUST_MASTER_T16000M_FCS_HH

#include "UsbDevice.hh"
#include "idf/T16000M.hh"

namespace idf {

/** USB ThrustMaster T.16000M FCS Joystick */
class UsbT16000M: public UsbDevice, public virtual T16000M {

    public:

    /** constructor*/
    UsbT16000M();

    virtual void decode(const std::vector<unsigned char> & data);

};

} // namespace idf

#endif