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
     * Performs communication and updates state. This function calls #open() first
     * if #isOpen() return @c false.
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
