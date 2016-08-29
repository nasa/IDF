#include "idf/SpaceMouse.hh"

namespace idf {

SpaceMouse::SpaceMouse() :
    button1(0, 1),
    button2(0, 1),
    button3(0, 1),
    button4(0, 1),
    buttonEsc(0, 1),
    buttonCtrl(0, 1),
    buttonAlt(0, 1),
    buttonShift(0, 1),
    buttonFlatRotation(0, 1),
    buttonT(0, 1),
    buttonR(0, 1),
    buttonF(0, 1),
    buttonMouseRotation(0, 1),
    buttonMenu(0, 1),
    buttonFit(0, 1) {}

}
