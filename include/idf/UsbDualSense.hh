/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDualSense.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDualSense.cpp}
 */

#ifndef USB_DUAL_SENSE_HH
#define USB_DUAL_SENSE_HH

#include "idf/UsbDualShock.hh"
#include "idf/DualSense.hh"

namespace idf {

/** USB Sony PlayStation 5 DualSense controller */
class UsbDualSense : public UsbDualShock, public DualSense {

    public:

    /** constructor */
    UsbDualSense();

    void decode(const std::vector<unsigned char>& data);

    void sendCommand();

};

}

#endif
