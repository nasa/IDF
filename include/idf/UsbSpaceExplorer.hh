/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbSpaceExplorer.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbSpaceExplorer.cpp}
 */

#ifndef USB_SPACE_EXPLORER_HH
#define USB_SPACE_EXPLORER_HH

#include "idf/UsbSpaceBase.hh"
#include "idf/SpaceExplorer.hh"

namespace idf {

/** USB SpaceExplorer mouse */
class UsbSpaceExplorer : public UsbSpaceBase, public SpaceExplorer {

    public:

    /** constructor */
    UsbSpaceExplorer();

    protected:

    void processButtons(const unsigned char* buttonData);

};

}

#endif
