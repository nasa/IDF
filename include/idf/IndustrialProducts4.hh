/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/IndustrialProducts4.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/IndustrialProducts4.cpp}
 */

#ifndef INDUSTRIAL_PRODUCTS4_HH
#define INDUSTRIAL_PRODUCTS4_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %IndustrialProducts4 hand controller's input layout
 *
 * @author Philip Kunz
 */
class IndustrialProducts4 : public virtual InputLayout {

    public:

    /** constructor */
    IndustrialProducts4();

    /** destructor */
    virtual ~IndustrialProducts4() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** the trigger button */
    SingleInput trigger;

    /** the grip button */
    SingleInput grip;

    /** the upper trigger of the switch */
    SingleInput switchUp;

    /** the lower trigger of the switch */
    SingleInput switchDown;

    /** up-down pivoting of the analog hat */
    SingleInput hatUpDownPivot;

    /** left-right pivoting of the analog hat */
    SingleInput hatLeftRightPivot;

    /** the upper button */
    SingleInput button1;

    /* the lower button*/
    SingleInput button2;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();
};

}

#endif
