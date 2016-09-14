/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMasterBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMasterBase.cpp}
 */

#ifndef THRUST_MASTER_BASE_HH
#define THRUST_MASTER_BASE_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * base input layout of a %ThrustMaster hand controller
 *
 * @author Derek Bankieris
 */
class ThrustMasterBase : public virtual InputLayout {

    public:

    /** constructor */
    ThrustMasterBase(bool isMale = false);

    /** destructor */
    virtual ~ThrustMasterBase() {};

    /**
     * describes the pin-out of the translational hand controller.
     * Male #upDownTranslation is inverted with respect to female.
     */
    const bool male;

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** forward-backward translation */
    SingleInput forwardBackwardTranslation;

    /** left-right translation */
    SingleInput leftRightTranslation;

    /** up-down translation */
    SingleInput upDownTranslation;

    /** the trigger */
    SingleInput trigger;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

    private:

    ThrustMasterBase& operator=(const ThrustMasterBase&);

};

}

#endif
