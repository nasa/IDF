/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbXBoxOne.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbXBoxOne.cpp}
 */

#ifndef USB_XBOX_ONE_WIRELESS_HH
#define USB_XBOX_ONE_WIRELESS_HH

#include "idf/UsbXBoxOne.hh"

namespace idf {

/** USB XBox One controller */
class BtXBoxOneWireless : public UsbDevice, public XBoxOne {

    public:

    /** constructor */
    BtXBoxOneWireless();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
