#include "inputAbstraction/include/Saitek.hh"

using namespace idf;

Saitek::Saitek() :
    leftPedal(0, 127),
    rightPedal(0, 127),
    twist(0, 511) {}
