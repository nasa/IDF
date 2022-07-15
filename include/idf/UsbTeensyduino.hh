/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbTeensyduino.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbTeensyduino.cpp}
 */

#ifndef USB_TEENSYDUINO_HH
#define USB_TEENSYDUINO_HH

#include "idf/UsbDevice.hh"
#include "idf/Teensyduino.hh"

namespace idf {

/** USB Teensyduino Pro Flight X52 Flight System */
class UsbTeensyduino : public UsbDevice, public Teensyduino {

    public:

    /** constructor */
    UsbTeensyduino();

    void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc UsbDevice::UsbDevice */
    UsbTeensyduino(const std::string& name, unsigned packetLength);
};

}

#endif
