/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/SpaceNavigator.cpp))
 */

#ifndef _SPACE_NAVIGATOR_HH_
#define _SPACE_NAVIGATOR_HH_

#include "SpaceBase.hh"
#include "SingleInput.hh"

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

    /** the left button */
    SingleInput leftButton;

    /** the right button */
    SingleInput rightButton;

};

}

#endif
