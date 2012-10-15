#ifndef _IO_EXCEPTION_HH_
#define _IO_EXCEPTION_HH_

#include <stdexcept>
#include <string>

namespace idf {

/**
 * represents an input/output exception
 *
 * @author Derek Bankieris
 */
class IOException : public std::runtime_error {

    public:

    /**
     * constructs a new instance
     *
     * @param message a description of the error
     */
    IOException(const char* message) :
        std::runtime_error(std::string(message)) {}

    /**
     * constructs a new instance
     *
     * @param message a description of the error
     */
    IOException(std::string& message) :
        std::runtime_error(message) {}

};

}

#endif
