/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/EthernetExtreme3dPro.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/EthernetExtreme3dPro.cpp}
 */

#ifndef ETHERNET_EXTREME_3D_PRO_HH
#define ETHERNET_EXTREME_3D_PRO_HH

#include "idf/EthernetDevice.hh"
#include "idf/Extreme3dPro.hh"

#include <string>

namespace idf {

class EthernetExtreme3dPro : public EthernetDevice, public Extreme3dPro {

    public:

    /** constructor */
    EthernetExtreme3dPro();

    void decode(const std::vector<unsigned char>& data);
    void sendCommand();

};

} // namespace

#endif