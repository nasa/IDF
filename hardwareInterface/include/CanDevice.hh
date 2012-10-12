/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/CanDevice.cpp))
 */

#ifndef _CAN_DEVICE_HH_
#define _CAN_DEVICE_HH_

#include "InputDevice.hh"
#include <vector>
#include <stdio.h>
#include <errno.h>

namespace hardware {

/**
 * abstract base class for all CAN input devices. Subclasses should usually
 * represent a specific physical device (WingMan, SpaceExplorer, etc) and
 * implement logic to fulfill the contract of <code>open</code>. They should
 * also usually derive from the appropriate class from the Input Abstraction
 * Layer, as well as be concrete.
 *
 * @author Derek Bankieris
 */
class CanDevice : public InputDevice {

    public:

    /**
     * constructs a new instance whose <code>open()</code> will look for a CAN
     * device
     *
     * @param networkID the target CAN device's vendorID
     * @param baudRate the target CAN device's productID
     */
    CanDevice(int networkID, int baudRate);

    /** destructs this instance */
    virtual ~CanDevice();

    virtual void open();

    virtual void close();

    protected:

    /** vendor ID, used to lookup this device in the CAN hierarchy */
    int mNetworkID;

    /** product IDs, used to lookup this device in the CAN hierarchy */
    int mBaudRate;

    private:

    /** number of instances in existance */
    static int instanceCount;

};

}

#endif
