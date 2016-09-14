/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SerialThrustMaster.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SerialThrustMaster.cpp}
 */

#ifndef SERIAL_THRUST_MASTER_HH
#define SERIAL_THRUST_MASTER_HH

#include "idf/SerialThrustMasterBase.hh"
#include "idf/ThrustMaster.hh"

namespace idf {

/**
 * shuttle-style serial %ThrustMaster hand controller
 *
 * @author Derek Bankieris
 */
class SerialThrustMaster : public SerialThrustMasterBase, public ThrustMaster {

    public:

    /**
     * constructs a new instance whose open() will open the serial port at @a path
     *
     * @param path @copydoc path
     * @param isMale @c true if the translational hand controller connector is male
     */
    SerialThrustMaster(const char* path = "idf/ttyS0", bool isMale = true);

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
