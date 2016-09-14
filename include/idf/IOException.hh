/*
PURPOSE:
*/

/* @trick_parse{everything} */

#ifndef IO_EXCEPTION_HH
#define IO_EXCEPTION_HH

#include <stdexcept>
#include <string>

namespace idf {

/**
 * input/output exception
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
    IOException(const std::string& message) :
        std::runtime_error(message) {}

};

}

#endif
