/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/ThrustMaster2.cpp}
 */

#ifndef _THRUST_MASTER2_HH_
#define _THRUST_MASTER2_HH_

#include "inputAbstraction/include/ThrustMasterBase.hh"
#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * Orion-style %ThrustMaster hand controller's input layout
 *
 * @author Derek Bankieris
 */
class ThrustMaster2 : public virtual ThrustMasterBase {

    public:

    /** constructor */
    ThrustMaster2(bool isMale = false);

    /** destructor */
    virtual ~ThrustMaster2() {};

    /** the left button */
    SingleInput leftButton;

    /** the middle button */
    SingleInput middleButton;

    /** the right button */
    SingleInput rightButton;

    private:

    ThrustMaster2& operator=(const ThrustMaster2&);

};

}

#endif
