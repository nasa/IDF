/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbThrustMasterWarthogStickBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbThrustMasterWarthogStickBase.cpp}
 */

#ifndef USB_THRUSTMASTER_WARTHOG_STICK_HH
#define USB_THRUSTMASTER_WARTHOG_STICK_HH

#include "idf/UsbDevice.hh"
#include "idf/ThrustMasterWarthogStickBase.hh"

namespace idf
{
/**
 * @brief Base layout of the ThrustMaster HOTAS WARTHOG Joystick
 * This device has a modular grip that can be replaced. Thus, the available
 * inputs are mostly just discrete buttons, which, for Windows OS would be
 * paired together into Hats and other composite inputs via the ThrustMaster
 * software.
 *
 * @author Philip Kunz
 */
class UsbThrustMasterWarthogStickBase : public UsbDevice, public ThrustMasterWarthogStickBase
{
public:

    /** constructor */
    UsbThrustMasterWarthogStickBase();

    virtual void decode(const std::vector<unsigned char> & data);

};

} // namespace idf

#endif
