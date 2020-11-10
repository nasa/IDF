/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbXBox.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbXBox.cpp}
 */

#ifndef USB_XBOX_HH
#define USB_XBOX_HH

#include "idf/UsbDevice.hh"
#include "idf/XBox.hh"

namespace idf {

/** USB XBox controller */
class UsbXBox : public UsbDevice, public XBox {

    public:

    /** constructor */
    UsbXBox();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
