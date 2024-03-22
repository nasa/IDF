/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/EthernetWingMan.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/EthernetWingMan.cpp}
 */

#ifndef ETHERNET_WING_MAN_HH
#define ETHERNET_WING_MAN_HH

#include "idf/EthernetDevice.hh"
#include "idf/WingMan.hh"

namespace idf {

/** ETHERNET WingMan joystick */
class EthernetWingMan : public EthernetDevice, public virtual WingMan {

    public:

    /** constructor */
    EthernetWingMan();

    virtual void decode(const std::vector<unsigned char>& data);

    protected:

    /** @copydoc EthernetDevice::EthernetDevice */
    EthernetWingMan(const std::string& name, unsigned packetLength);

};

}

#endif
