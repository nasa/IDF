/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/UsbSpaceBase.cpp))
 */

#ifndef _USB_SPACE_BASE_HH_
#define _USB_SPACE_BASE_HH_

#include "UsbDevice.hh"
#include "inputAbstraction/include/SpaceBase.hh"

namespace idf {

/**
 * represents the common aspects of all 3dconnexion controllers
 *
 * @author Derek Bankieris
 */
class UsbSpaceBase : public UsbDevice, public virtual SpaceBase {

    public:

    /** constructor */
    UsbSpaceBase(int vendorID, int productID);

    /**
     * updates this instance so that it reflects the target device's current
     * state
     *
     * @throws IOException if the device is not open
     */
    void update();

    protected:

    /**
     * processes the button data and sets the appropriate inputs. This function
     * is called by <code>update()</code> and is where derived classes should
     * address their specific button layouts.
     *
     * @param buttonData the raw button data
     */
    virtual void processButtons(unsigned char* buttonData) = 0;

};

}

#endif
