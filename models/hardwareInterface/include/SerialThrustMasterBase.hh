/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/SerialThrustMasterBase.cpp))
 */

#ifndef _SERIAL_THRUST_MASTER_BASE_HH_
#define _SERIAL_THRUST_MASTER_BASE_HH_

#include "SerialDevice.hh"
#include "inputAbstraction/include/ThrustMasterBase.hh"

namespace idf {

/**
 * represents the common aspects of all ThrustMaster hand controllers
 *
 * @author Derek Bankieris
 */
class SerialThrustMasterBase : public SerialDevice, public virtual ThrustMasterBase {

    public:

    /** constructor */
    SerialThrustMasterBase(const char *path = "/dev/ttyS0", bool isMale = false);

    /** opens this device for communication */
    void open();

    /**
     * updates this instance so that it reflects the target device's current
     * state
     *
     * @throws IOException if the device is not open
     */
    void update();


    protected:

    /**
     * processes the byte containing button data and sets the appropriate
     * inputs. This function is called by <code>update()</code> and is where
     * derived classes should address their specific button layouts.
     *
     * @param buttonByte the raw button data
     */
    virtual void processButtons(unsigned char buttonByte) = 0;

};

}

#endif
