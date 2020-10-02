/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbGravis.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbGravis.cpp}
 */

#ifndef USB_GRAVIS_HH
#define USB_GRAVIS_HH

#include "idf/UsbDevice.hh"
#include "idf/Gravis.hh"

namespace idf {

/** USB Gravis game controller */
class UsbGravis : public UsbDevice, public Gravis {

    public:

    /** constrcutor */
    UsbGravis();

    void decode(const std::vector<unsigned char>& data);

};

}

#endif
