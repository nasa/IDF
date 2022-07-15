/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Er7Orion.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Er7Orion.cpp}
 */

#ifndef ER7_ORION_HH
#define ER7_ORION_HH

#include "idf/ThrustMasterBase.hh"
#include "idf/SingleInput.hh"

namespace idf {

/** %Er7Orion hand controller's input layout */
class Er7Orion : public virtual ThrustMasterBase {

    public:

    /** constructor */
    Er7Orion();

    /** destructor */
    virtual ~Er7Orion() {};

    /** the left button, labelled CFS */
    SingleInput cfsButton;

    /** the middle button, labelled BFS */
    SingleInput bfsButton;

    /** the right button, unlabelled */
    SingleInput rhcButton;

    /** the button on the side, labelled abort */
    SingleInput abortButton;

    /** the trigger */
    SingleInput trigger;

    /** the button on the translational hand controller */
    SingleInput thcButton;

    private:

    Er7Orion& operator=(const Er7Orion&);

};

}

#endif
