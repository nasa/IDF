/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/IndustrialProducts2.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/IndustrialProducts2.cpp}
 */

#ifndef INDUSTRIAL_PRODUCTS2_HH
#define INDUSTRIAL_PRODUCTS2_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %IndustrialProducts2 hand controller's input layout
 *
 * @author Derek Bankieris
 */
class IndustrialProducts2 : public virtual InputLayout {

    public:

    /** constructor */
    IndustrialProducts2();

    /** destructor */
    virtual ~IndustrialProducts2() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** twisting */
    SingleInput twist;

    /** the trigger button */
    SingleInput trigger;

    /** the digital hat's northern trigger */
    SingleInput hatNorth;

    /** the digital hat's eastern trigger */
    SingleInput hatEast;

    /** the digital hat's southern trigger */
    SingleInput hatSouth;

    /** the digital hat's western trigger */
    SingleInput hatWest;

    /** the northwest button */
    SingleInput northWestButton;

    /** the southwest button */
    SingleInput southWestButton;

    /** the northeast button */
    SingleInput northEastButton;

    /** the southeast button */
    SingleInput southEastButton;

};

}

#endif
