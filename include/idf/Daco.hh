/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Daco.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Daco.cpp}
 */

#ifndef DACO_HH
#define DACO_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Daco DF0201 3 Axes 5 Switch Controller input layout
 *
 * @author Philip Kunz
 */
class Daco : public virtual InputLayout {

   public:

   /** constructor */
   Daco();

   /** destructor */
   virtual ~Daco() {};

   /** x axis */
   SingleInput x;

   /** y axis */
   SingleInput y;

   /** z axis */
   SingleInput z;

   /** switch */
   SingleInput switch1;

   protected:

   virtual const std::vector<Configurable>& getConfigurables();

};

} // namespace

#endif
