/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/ThrustMaster2.cpp))
 */

#ifndef _THRUST_MASTER2_HH_
#define _THRUST_MASTER2_HH_

#include "ThrustMasterBase.hh"
#include "SingleInput.hh"

namespace idf {

/**
 * represents an Orion-style ThrustMaster hand controller's input layout
 *
 * @author Derek Bankieris
 */
class ThrustMaster2 : public virtual ThrustMasterBase {

    public:

    /** the left button */
    SingleInput leftButton;

    /** the middle button */
    SingleInput middleButton;

    /** the right button */
    SingleInput rightButton;

    /** constructor */
    ThrustMaster2(bool isMale = false);

    private:

    /** this class is not copy-assignable */
    ThrustMaster2& operator=(const ThrustMaster2&);

};

}

#endif
