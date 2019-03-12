/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Deadbandable.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Deadbandable.cpp}
 */

#ifndef DEADBANDABLE_HH
#define DEADBANDABLE_HH

#include <vector>
#include "idf/Deadband.hh"

namespace idf {

/**
 * this is a mixin class that provides the adopting class with Deadband support
 *
 * @author Derek Bankieris
 */
class Deadbandable {

    public:

    /** destructor */
    ~Deadbandable() {}

    /**
     * adds @a deadband to the list of filters to be applied to raw values.
     * Adding a deadband that is already applied to this instance has no effect.
     *
     * @param deadband the raw deadband to add
     */
    void addDeadband(const Deadband& deadband);

    /**
     * adds @a deadband to the list of filters to be applied to normalized values.
     * Adding a deadband that is already applied to this instance has no effect.
     *
     * @param deadband the normalized deadband to add
     */
    void addNormalizedDeadband(const Deadband& deadband);

    /**
     * remove @a deadband from the list of filters.
     * Removing a deadband that is not applied to this instance has no effect.
     *
     * @param deadband the deadband to remove
     */
    void removeDeadband(const Deadband& deadband);

    /** removes all deadbands applied to this instance */
    void clearDeadbands();

    /**
     * returns the raw deadbands applied to this instance
     *
     * @return the current raw deadbands
     */
    const std::vector<Deadband>& getDeadbands() const;

    /**
     * returns the normalized deadbands applied to this instance
     *
     * @return the current normalized deadbands
     */
    const std::vector<Deadband>& getNormalizedDeadbands() const;

    protected:

    /**
     * adds @a deadband to @a deadbands
     * Adding a deadband that is already applied to this instance has no effect.
     *
     * @param deadband the deadband to add
     * @param filters the vector to which to add the deadband
     */
    void addDeadband(const Deadband& deadband, std::vector<Deadband>& filters);

    /**
     * applies all Deadbands in @a filters to @a value
     *
     * @param value the value to filter
     * @param filters the deadbands to apply
     *
     * @return the filtered value
     */
    double applyDeadbands(double value, const std::vector<Deadband>& filters) const;

    /**
     * applies all raw Deadbands to @a value
     *
     * @param value the value to filter
     *
     * @return the filtered value
     */
    double applyDeadbands(double value) const;

    /**
     * applies all normalized Deadbands to @a value
     *
     * @param value the value to filter
     *
     * @return the filtered value
     */
    double applyNormalizedDeadbands(double value) const;

    /** raw deadband filters */
    std::vector<Deadband> deadbands;

    /** normalized deadband filters */
    std::vector<Deadband> normalizedDeadbands;

};

}

#endif
