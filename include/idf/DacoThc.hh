/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/DacoThc.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/DacoThc.cpp}
 */

#ifndef DACO_THC_HH
#define DACO_THC_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %DacoThc DF0201 3 Axes 5 Switch Controller input layout
 *
 * @author Philip Kunz
 */
class DacoThc : public virtual InputLayout {

   public:

   /** constructor */
   DacoThc();

   /** destructor */
   virtual ~DacoThc() {};

   /** forward backward */
   SingleInput forwardBackwardTranslation;

   /** y axis */
   SingleInput leftRightTranslation;

   /** z axis */
   SingleInput upDownTranslation;

   /** switch */
   SingleInput switch1;

   protected:

   virtual const std::vector<Configurable>& getConfigurables();

};

} // namespace

#endif
