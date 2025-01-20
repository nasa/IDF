/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDaco.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDaco.cpp}
 */

#ifndef USB_DACO_HH
#define USB_DACO_HH

#include "idf/UsbDevice.hh"
#include "idf/Daco.hh"

namespace idf {

/** USB Daco DF0201 3 Axis 5 Switch Controller */
class UsbDaco : public UsbDevice, public Daco {

   public:

   /* constructor */
   UsbDaco();

   void decode(const std::vector<unsigned char>& data);

};

} // namespace idf

#endif
