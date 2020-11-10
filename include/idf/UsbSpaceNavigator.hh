/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSpaceNavigator.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSpaceNavigator.cpp}
 */

#ifndef USB_SPACE_NAVIGATOR_HH
#define USB_SPACE_NAVIGATOR_HH

#include "idf/UsbSpaceBase.hh"
#include "idf/SpaceNavigator.hh"

namespace idf {

/** USB SpaceNavigator mouse */
class UsbSpaceNavigator : public UsbSpaceBase, public SpaceNavigator {

    public:

    /** constructor */
    UsbSpaceNavigator();

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
