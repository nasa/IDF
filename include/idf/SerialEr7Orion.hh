/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SerialEr7Orion.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SerialEr7Orion.cpp}
 */

#ifndef SERIAL_ER7_ORION_HH
#define SERIAL_ER7_ORION_HH

#include "idf/SerialThrustMasterBase.hh"
#include "idf/Er7Orion.hh"

namespace idf {

/** serial %Er7Orion hand controller */
class SerialEr7Orion : public SerialThrustMasterBase, public Er7Orion {

    public:

    /**
     * constructs a new instance whose open() will open the serial port at @a path
     *
     * @param path @copydoc path
     */
    SerialEr7Orion(const char *path = "/dev/ttyACM0", bool isMale = true);

    void decode(const std::vector<unsigned char>& data);

    protected:

    /**
     * processes the byte containing button data and sets the appropriate inputs
     *
     * @param buttonByte the raw button data
     */
    void processButtons(unsigned char buttonByte);

};

}

#endif
