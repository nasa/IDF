/*
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/SerialDevice.cpp))
 */

#ifndef _SERIAL_DEVICE_HH_
#define _SERIAL_DEVICE_HH_

#include "hardwareInterface/include/InputDevice.hh"

#include <string>

namespace idf {

/**
 * abstract base class for all serial input devices. Subclasses should usually
 * represent a specific physical device (WingMan, SpaceExplorer, etc) and
 * implement logic to fulfill the contract of <code>open</code>. They should
 * also usually derive from the appropriate class from the Input Abstraction
 * Layer, as well as be concrete.
 *
 * @author Derek Bankieris
 */
class SerialDevice : public InputDevice {

    public:

    /**
     * constructs a new instance whose <code>open()</code> will open the serial
     * port at <code>path</code>
     *
     * @param name the name of this device
     * @param system path to the terminal to which the device is attached
     */
    SerialDevice(const std::string& name, const char *path);

    /** destructor */
    virtual ~SerialDevice() {};

    /** opens this device for communication */
    virtual void open();

    /** closes this device */
    virtual void close();

    protected:

    /** handle to the device */
    int handle;

    /**
     * reads <code>length</code> bytes from this device and stores them in
     * <code>buffer</code>
     *
     * @param buffer the location to store the data
     * @param length the number of bytes to read
     *
     * @return the number of bytes read (always non-negative)
     *
     * @throws IOException if an error occurs while reading or if the device
     * is not open
     */
    virtual int read(unsigned char *buffer, size_t length);

    /**
     * writes <code>length</code> bytes from <code>buffer</code> to this device
     *
     * @param buffer the location of the data to write
     * @param length the number of bytes to write
     *
     * @return the number of bytes written (always non-negative)
     *
     * @throws IOException if an error occurs while writing or if the device
     * is not open
     */
    virtual int write(const void *buffer, size_t length);

    protected:

    /** terminal path */
    std::string path;

};

}

#endif
