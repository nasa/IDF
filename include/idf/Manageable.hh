/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Manageable.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Manageable.cpp}
 */

#ifndef MANAGEABLE_HH
#define MANAGEABLE_HH

namespace idf {

/**
 * @author Derek Bankieris
 */
class Manageable {

    public:

    /** constructor */
    Manageable();

    /** destructor */
    virtual ~Manageable() {};

    /**
     * opens communication channels
     *
     * @throws IOException if an error occurs
     */
    virtual void open() = 0;

    /**
     * Updates this instance's state to reflect the latest data from the device
     * at the cost of missing inputs that are applied and removed between calls.
     * See #InputDevice::updateOnce() for a loss-free version. This function
     * calls #open() first if #isOpen() returns @c false.
     *
     * @throws IOException if an error occurs while opening or updating
     */
    virtual void update() = 0;

    /**
     * closes communication channels
     *
     * @throws IOException if an error occurs
     */
    virtual void close() = 0;

    /**
     * gets the communication state
     *
     * @returns @a True if communication has been established
     *          @a False if it hasn't
     */
    virtual bool isOpen() const;

    protected:

    /** the communication state */
    bool mOpen;

};

}

#endif
