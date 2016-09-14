/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMaster2.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMaster2.cpp}
 */

#ifndef THRUST_MASTER2_HH
#define THRUST_MASTER2_HH

#include "idf/ThrustMasterBase.hh"
#include "idf/SingleInput.hh"

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
