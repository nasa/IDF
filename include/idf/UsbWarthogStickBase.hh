/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbWarthogStickBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbWarthogStickBase.cpp}
 */

#ifndef USB_THRUSTMASTER_WARTHOG_STICK_HH
#define USB_THRUSTMASTER_WARTHOG_STICK_HH

#include "idf/UsbDevice.hh"
#include "idf/WarthogStickBase.hh"

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
class UsbWarthogStickBase : public UsbDevice, public WarthogStickBase
{
public:

    /** constructor */
    UsbWarthogStickBase();

    virtual void decode(const std::vector<unsigned char> & data);

};

} // namespace idf

#endif
