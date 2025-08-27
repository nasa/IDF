/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbVirpilConstellationAlpha.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbVirpilConstellationAlpha.cpp}
 */

#ifndef USB_VIRPIL_CONSTELLATION_ALPHA_HH
#define USB_VIRPIL_CONSTELLATION_ALPHA_HH

#include "idf/UsbDevice.hh"
#include "idf/VirpilConstellationAlpha.hh"

namespace idf {

/** Virpil Constellation Alpha on a Virpil MongoosT-50CM3 base */
class UsbVirpilConstellationAlpha : public UsbDevice, public VirpilConstellationAlpha {

   public:

   /* constructor */
   UsbVirpilConstellationAlpha();

   void decode(const std::vector<unsigned char>& data);

};

} // namespace idf

#endif
