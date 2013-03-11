/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/SerialThrustMaster.cpp))
 */

#ifndef _SERIAL_THRUST_MASTER_HH_
#define _SERIAL_THRUST_MASTER_HH_

#include "SerialThrustMasterBase.hh"
#include "inputAbstraction/include/ThrustMaster.hh"

namespace idf {

/**
 * represents a shuttle-style serial ThrustMaster hand controller
 *
 * @author Derek Bankieris
 */
class SerialThrustMaster : public SerialThrustMasterBase, public ThrustMaster {

    public:

    /** constructor */
    SerialThrustMaster(const char *path = "/dev/ttyS0", bool isMale = true);

    protected:

    /**
     * processes the byte containing button data and sets the appropriate
     * inputs
     *
     * @param buttonByte the raw button data
     */
    void processButtons(unsigned char buttonByte);

};

}

#endif
