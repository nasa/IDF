/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSpaceMouse.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSpaceMouse.cpp}
 */

#ifndef USB_SPACE_MOUSE_HH
#define USB_SPACE_MOUSE_HH

#include "idf/UsbSpaceBase.hh"
#include "idf/SpaceMouse.hh"

namespace idf {

/** USB SpaceMouse */
class UsbSpaceMouse : public UsbSpaceBase, public SpaceMouse {

    public:

    /** constructor */
    UsbSpaceMouse();

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
