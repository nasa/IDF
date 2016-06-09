/**
 * @trick_parse{everything}
 * @trick_link_dependency{hardwareInterface/src/InputDevice.cpp}
 */

#ifndef INPUT_DEVICE_HH
#define INPUT_DEVICE_HH

#include "inputAbstraction/include/InputLayout.hh"
#include <list>
#include <string>
#include <utility>
#include <vector>

namespace idf {

/**
 * abstract base class for all input devices. Subclasses should usually be
 * abstract, represent collections of input devices that communicate via a
 * specific protocol (usb, serial, Bluetooth, etc), and encapsulate data
 * and functions particular to and shared across all devices of that type.
 *
 * @author Derek Bankieris
 */
class InputDevice : public virtual InputLayout {

    public:

    /** an identifying name for this device */
    const std::string name;

    /** the amount of time in seconds to delay processing of data from the phyiscal device */
    double delay; // (s)

    /** @c false to discard data from the physical device */
    bool enabled;

    /**
     * constructor
     *
     * @param name @copydoc name
     */
    InputDevice(const std::string& name);

    /** destructor */
    virtual ~InputDevice() {};

    /** opens this device for communication */
    virtual void open() = 0;

    /** closes this device */
    virtual void close() = 0;

    /**
     * returns the open state of this device
     *
     * @return @c true if this device is open
     */
    virtual bool isOpen() const;

    /**
     * updates this instance so that it reflects the target device's current state.
     * This function calls #open() if #isOpen() return @c false.
     *
     * @throws IOException if an error occurs while opening or updating
     */
    void update();

    /** interactively configures all inputs */
    virtual void configure();

    protected:

    /** the open state of this device */
    bool mOpen;

    /**
     * reads all pending data from this device
     *
     * @return a collection of state packets
     */
    virtual std::vector<std::vector<unsigned char> > read() = 0;

    /**
     * decodes @a data, updating this device's fields to reflect the described state
     *
     * @param data raw data describing the device's state
     */
    virtual void decode(const std::vector<unsigned char>& data) = 0;

    private:

    /** a time-stamped byte array, used to implement delays */
    class Entry {

        public:

        /** the raw data describing the device's state */
        const std::vector<unsigned char> data;

        /** the time at which this data should be considered avaiable */
        const double targetTime;

        /**
         * constructor
         *
         * @param data @copydoc data
         * @param delay the amount of time in seconds that processing of this data should be delayed
         */
        Entry(std::vector<unsigned char> data, double delay);
    };

    /** the queue of data entries waiting to be processed */
    std::list<Entry*> storage;

    /**
     * gets the time in seconds since some arbitrary but fixed point in the past
     *
     * @return the time
     */
    static double getTime();

    /**
     * interactively configures @a inputs
     *
     * @param inputs the inputs to configure
     */
    virtual void configure(const std::vector<Configurable>& inputs);

};

}

#endif
