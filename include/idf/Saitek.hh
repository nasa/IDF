/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Saitek.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Saitek.cpp}
 */

#ifndef SAITEK_HH
#define SAITEK_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Saitek Pro Flight Rudder Pedals input layout
 *
 * @author Derek Bankieris
 */
class Saitek : public virtual InputLayout {

    public:

    /** constructor */
    Saitek();

    /** destructor */
    virtual ~Saitek() {};

    /** the left foot pedal */
    SingleInput leftPedal;

    /** the right foot pedal */
    SingleInput rightPedal;

    /** the movement of both foot pedals about the center circle */
    SingleInput twist;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
