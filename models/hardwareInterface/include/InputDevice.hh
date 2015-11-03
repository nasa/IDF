/*
 PURPOSE:
 ()

 LIBRARY DEPENDENCIES:
 ((hardwareInterface/src/InputDevice.cpp))
*/

#ifndef INPUT_DEVICE_HH
#define INPUT_DEVICE_HH

// HACK - remove when long-term solution is implemented
#include <list>
#include  <time.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
#endif
// HACK

namespace idf {

/**
 * abstract base class for all input devices. Subclasses should usually be
 * abstract, represent collections of input devices that communicate via a
 * specific protocol (usb, serial, Bluetooth, etc), and encapsulate data
 * and functions particular to and shared across all devices of that type.
 *
 * @author Derek Bankieris
 */
class InputDevice {

    public:

    /** constructor */
    InputDevice();

    /** destructor */
    virtual ~InputDevice() {};

    /** opens this device for communication */
    virtual void open() = 0;

    /** closes this device */
    virtual void close() = 0;

    /**
     * returns the open state of this device
     *
     * @return whether or not this device is open
     */
    virtual bool isOpen() const;

    /**
     * updates this instance so that it reflects the target device's current
     * state
     *
     * @throws IOException if the device is not open
     */
    virtual void update();

    /** HACK - short-term solution only */
    double delay;
    bool enabled;
    /** HACK  ************************************************/

    protected:

    /** the open state of this device */
    bool mOpen;

    /** HACK - short-term solution only */
    static double getTime() {
        #ifdef __APPLE__
        static mach_timebase_info_data_t timebase = {};
        if (timebase.denom == 0) {
            mach_timebase_info(&timebase);
        }
        return mach_absolute_time() * timebase.numer / timebase.denom / 1E9;
        #else
        struct timespec time = {0, 0};
        clock_gettime(CLOCK_MONOTONIC, &time);
        return time.tv_sec + time.tv_sec / 1E9;
        #endif
    }

    class Entry {
        public:
        unsigned char* data;
        double targetTime;
        Entry(unsigned int size, double delay) :
            data(new unsigned char[size]()),
            targetTime(InputDevice::getTime() + delay) {}
        ~Entry() {
            delete[] data;
        }
    };

    std::list<Entry*> storage;
    /** HACK  ************************************************/
};

}

#endif
