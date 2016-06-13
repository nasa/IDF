/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/Saitek.cpp}
 */

#ifndef _SAITEK_HH_
#define _SAITEK_HH_

#include "inputAbstraction/include/InputLayout.hh"
#include "inputAbstraction/include/SingleInput.hh"

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
