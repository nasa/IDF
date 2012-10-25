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

namespace idf {

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
     * constructs a new instance
     */
    CanDevice();

    /** destructs this instance */
    virtual ~CanDevice();

    virtual void open();

    virtual void close();

};

}

#endif
