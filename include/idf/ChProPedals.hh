/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ChProPedals.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ChProPedals.cpp}
 */

#ifndef _CH_PRO_PEDALS_HH_
#define _CH_PRO_PEDALS_HH_

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %ChProPedals Pro Flight Rudder Pedals input layout
 *
 * @author Derek Bankieris
 */
class ChProPedals : public virtual InputLayout {

    public:

    /** constructor */
    ChProPedals();

    /** destructor */
    virtual ~ChProPedals() {};

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
