/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/SpaceNavigator.cpp}
 */

#ifndef _SPACE_NAVIGATOR_HH_
#define _SPACE_NAVIGATOR_HH_

#include "inputAbstraction/include/SpaceBase.hh"
#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * represents a SpaceNavigator hand controller's input layout
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
