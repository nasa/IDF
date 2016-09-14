/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SpaceBase.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SpaceBase.cpp}
 */

#ifndef SPACE_BASE_HH
#define SPACE_BASE_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * base layout of a 3dconnexion controller
 *
 * @author Derek Bankieris
 */
class SpaceBase : public virtual InputLayout {

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

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
