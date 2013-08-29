/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/ChProPedals.cpp))
 */

#ifndef _CH_PRO_PEDALS_HH_
#define _CH_PRO_PEDALS_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a ChProPedals Pro Flight Rudder Pedals input layout
 *
 * @author Derek Bankieris
 */
class ChProPedals {

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

};

}

#endif
