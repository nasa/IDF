/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbThrustMasterJoystickHotas.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbThrustMasterJoystickHotas.cpp}
 */

#ifndef USB_THRUSTMASTER_JOYSTICK_HOTAS_HH
#define USB_THRUSTMASTER_JOYSTICK_HOTAS_HH

#include "idf/UsbDevice.hh"
#include "idf/ThrustMasterJoystickHotas.hh"

namespace idf {

/** USB ThrustMaster Joystick HOTAS */
class UsbThrustMasterJoystickHotas : public UsbDevice, public ThrustMasterJoystickHotas {

    public:

    /** constructor */
    UsbThrustMasterJoystickHotas();

    void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbThrustMasterJoystickHotas(const std::string& name, unsigned packetLength);
};

}

#endif
