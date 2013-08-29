/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/Saitek.cpp))
 */

#ifndef _SAITEK_HH_
#define _SAITEK_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a Saitek Pro Flight Rudder Pedals input layout
 *
 * @author Derek Bankieris
 */
class Saitek {

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

};

}

#endif
