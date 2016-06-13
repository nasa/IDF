/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/SerialThrustMasterBase.cpp}
 */

#ifndef _SERIAL_THRUST_MASTER_BASE_HH_
#define _SERIAL_THRUST_MASTER_BASE_HH_

#include "hardwareInterface/include/SerialDevice.hh"
#include "inputAbstraction/include/ThrustMasterBase.hh"

namespace idf {

/**
 * common aspects of all %ThrustMaster hand controllers
 *
 * @author Derek Bankieris
 */
class SerialThrustMasterBase : public SerialDevice, public virtual ThrustMasterBase {

    public:

    /**
     * @copydoc SerialDevice::SerialDevice
     * @param isMale @c true if the translational hand controller connector is male
     */
    SerialThrustMasterBase(const std::string& name, const char *path = "/dev/ttyS0", bool isMale = false);

    /** destructor */
    virtual ~SerialThrustMasterBase() {};

    void open();
    std::vector<std::vector<unsigned char> > read();
    void decode(const std::vector<unsigned char>& data);

    protected:

    /**
     * processes the byte containing button data and sets the appropriate
     * inputs. This function is called by update() and is where
     * derived classes should address their specific button layouts.
     *
     * @param buttonByte the raw button data
     */
    virtual void processButtons(unsigned char buttonByte) = 0;
};

}

#endif
