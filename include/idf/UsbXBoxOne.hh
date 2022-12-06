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

#ifndef USB_XBOX_ONE_HH
#define USB_XBOX_ONE_HH

#include "idf/UsbDevice.hh"
#include "idf/XBoxOne.hh"

namespace idf {

/** USB XBox One controller */
class UsbXBoxOne : public UsbDevice, public XBoxOne {

    public:

    /** constructor */
    UsbXBoxOne();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
