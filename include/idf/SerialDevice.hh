/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SerialDevice.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SerialDevice.cpp}
 */

#ifndef _SERIAL_DEVICE_HH_
#define _SERIAL_DEVICE_HH_

#include "idf/InputDevice.hh"

#include <string>

namespace idf {

/**
 * abstract base class for all serial input devices. Subclasses should usually
 * represent a specific physical device (WingMan, SpaceExplorer, etc) and
 * implement logic to fulfill the contract of open(). They should
 * also usually derive from the appropriate class from the %Input Abstraction
 * Layer, as well as be concrete.
 *
 * @author Derek Bankieris
 */
class SerialDevice : public InputDevice {

    public:

    /**
     * constructs a new instance whose open() will open the serial port at @a path
     *
     * @param name the name of this device
     * @param path @copydoc path
     */
    SerialDevice(const std::string& name, const char *path);

    /** destructor */
    virtual ~SerialDevice() {};

    virtual void open();
    virtual void close();

    using InputDevice::read;

    protected:

    /** handle to the device */
    int handle;

    /**
     * reads @a length bytes from this device and stores them in @a buffer
     *
     * @param buffer the location to store the data
     * @param length the number of bytes to read
     *
     * @return the number of bytes read (always non-negative)
     *
     * @throws IOException if an error occurs while reading or if the device is not open
     */
    virtual int read(unsigned char *buffer, size_t length);

    /**
     * writes @a length bytes from @a buffer to this device
     *
     * @param buffer the location of the data to write
     * @param length the number of bytes to write
     *
     * @return the number of bytes written (always non-negative)
     *
     * @throws IOException if an error occurs while writing or if the device is not open
     */
    virtual int write(const void *buffer, size_t length);

    protected:

    /** system path to the terminal to which the device is attached */
    std::string path;

};

}

#endif
