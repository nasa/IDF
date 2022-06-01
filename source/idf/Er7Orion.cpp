#include "idf/Er7Orion.hh"

namespace idf {

Er7Orion::Er7Orion() :
    ThrustMasterBase(false),
    cfsButton(0, 1),
    bfsButton(0, 1),
    rhcButton(0, 1),
    abortButton(0, 1),
    trigger(0, 1),
    thcButton(0, 1) {}

}
