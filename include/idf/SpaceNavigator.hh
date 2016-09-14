/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SpaceNavigator.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SpaceNavigator.cpp}
 */

#ifndef SPACE_NAVIGATOR_HH
#define SPACE_NAVIGATOR_HH

#include "idf/SpaceBase.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %SpaceNavigator hand controller's input layout
 *
 * @author Derek Bankieris
 */
class SpaceNavigator : public virtual SpaceBase {

    public:

    /** constructor */
    SpaceNavigator();

    /** destructor */
    virtual ~SpaceNavigator() {};

    /** the left button */
    SingleInput leftButton;

    /** the right button */
    SingleInput rightButton;

};

}

#endif
