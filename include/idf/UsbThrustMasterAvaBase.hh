/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbThrustMasterAvaBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbThrustMasterAvaBase.cpp}
 */

#ifndef USB_THRUSTMASTER_AVA_BASE_HH
#define USB_THRUSTMASTER_AVA_BASE_HH

#include "idf/UsbDevice.hh"
#include "idf/ThrustMasterAvaBase.hh"

namespace idf {

/** USB ThrustMasterAvaBase joystick */
class UsbThrustMasterAvaBase : public UsbDevice, public virtual ThrustMasterAvaBase {

    public:

    /** constructor */
    UsbThrustMasterAvaBase();

    virtual void decode(const std::vector<unsigned char>& data);

};

} // name space idf

#endif
