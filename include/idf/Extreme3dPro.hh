/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Extreme3dPro.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Extreme3dPro.cpp}
 */

#ifndef _EXTREME_3D_PRO_HH_
#define _EXTREME_3D_PRO_HH_

#include "idf/WingMan.hh"

namespace idf {

/**
 * %Extreme3dPro hand controller's input layout
 *
 * @author Derek Bankieris
 */
class Extreme3dPro : public virtual WingMan {

    public:

    /** constructor */
    Extreme3dPro();

    /** destructor */
    virtual ~Extreme3dPro() {};

    /** the button labeled 08 */
    SingleInput button8;

    /** the button labeled 09 */
    SingleInput button9;

    /** the button labeled 010 */
    SingleInput button10;

    /** the button labeled 011 */
    SingleInput button11;

    /** the button labeled 012 */
    SingleInput button12;

};

}

#endif
