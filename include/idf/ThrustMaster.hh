/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMaster.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMaster.cpp}
 */

#ifndef THRUST_MASTER_HH
#define THRUST_MASTER_HH

#include "idf/ThrustMasterBase.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * shuttle-style %ThrustMaster hand controller's input layout
 *
 * @author Derek Bankieris
 */
class ThrustMaster : public virtual ThrustMasterBase {

    public:

    /** constructor */
    ThrustMaster(bool isMale = false);

    /** destructor */
    virtual ~ThrustMaster() {};

    /** the switch */
    SingleInput topSwitch;

    /** the top button */
    SingleInput topButton;

    /** the left three-state switch */
    SingleInput leftSwitch;

    /** the right three-state switch */
    SingleInput rightSwitch;

    private:

    ThrustMaster& operator=(const ThrustMaster&);

};

}

#endif
