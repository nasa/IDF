/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/SerialThrustMaster.cpp))
 */

#ifndef _SERIAL_THRUST_MASTER_HH_
#define _SERIAL_THRUST_MASTER_HH_

#include "SerialDevice.hh"
#include "inputAbstraction/include/ThrustMaster.hh"

namespace idf {

/**
 * represents a serial ThrustMaster hand controller
 *
 * @author Derek Bankieris
 */
class SerialThrustMaster : public SerialDevice, public ThrustMaster {

    public:

    /** constructor */
    SerialThrustMaster(const char *path = "/dev/ttyS0", bool isMale = false);

    void update();


};

}

#endif
