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

    /** opens this device for communication */
    void open();

    /**
     * updates this instance so that it reflects the target device's current
     * state
     *
     * @throws IOException if the device is not open
     */
    void update();


};

}

#endif
