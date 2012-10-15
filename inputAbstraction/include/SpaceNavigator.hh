/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/SpaceNavigator.cpp))
 */

#ifndef _SPACE_NAVIGATOR_HH_
#define _SPACE_NAVIGATOR_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a SpaceNavigator hand controller's input layout
 *
 * @author Derek Bankieris
 */
class SpaceNavigator {

    public:

    /** constructor */
    SpaceNavigator();

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

};

}

#endif
