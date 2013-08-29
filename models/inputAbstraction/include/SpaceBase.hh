/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/SpaceBase.cpp))
 */

#ifndef _SPACE_BASE_HH_
#define _SPACE_BASE_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents the base layout of a 3dconnexion controller
 *
 * @author Derek Bankieris
 */
class SpaceBase {

    public:

    /** constructor */
    SpaceBase();

    /** destructor */
    virtual ~SpaceBase() {};

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
