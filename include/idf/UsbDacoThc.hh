/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/UsbDacoThc.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/UsbDacoThc.cpp}
 */

#ifndef USB_DACO_THC_HH
#define USB_DACO_THC_HH

#include "idf/UsbDevice.hh"
#include "idf/DacoThc.hh"

namespace idf {

/** USB DacoThc DF0201 3 Axis 5 Switch Controller */
class UsbDacoThc : public UsbDevice, public DacoThc {

   public:

   /* constructor */
   UsbDacoThc();

   void decode(const std::vector<unsigned char>& data);

};

} // namespace idf

#endif
