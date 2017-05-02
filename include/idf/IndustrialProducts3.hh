/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/IndustrialProducts3.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/IndustrialProducts3.cpp}
 */

#ifndef INDUSTRIAL_PRODUCTS3_HH
#define INDUSTRIAL_PRODUCTS3_HH

#include "idf/IndustrialProducts.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %IndustrialProducts3 hand controller's input layout
 *
 * @author Derek Bankieris
 */
class IndustrialProducts3 : public IndustrialProducts {

    public:

    /** constructor */
    IndustrialProducts3();

    /** destructor */
    virtual ~IndustrialProducts3() {};

    /** the face button */
    SingleInput button;

};

}

#endif
