#include "SpaceExplorer.hh"

using namespace idf;

SpaceExplorer::SpaceExplorer() :
    forwardBackwardPivot(-350, 350, 0),
    leftRightPivot(-350, 350, 0),
    twist(-350, 350, 0),
    forwardBackwardTranslation(-350, 350, 0),
    leftRightTranslation(-350, 350, 0),
    upDownTranslation(-350, 350, 0),
    button1(0, 1),
    button2(0, 1),
    buttonMinus(0, 1),
    buttonPlus(0, 1),
    buttonEsc(0, 1),
    buttonCtrl(0, 1),
    buttonAlt(0, 1),
    buttonShift(0, 1),
    buttonT(0, 1),
    buttonL(0, 1),
    buttonR(0, 1),
    button2d(0, 1),
    buttonF(0, 1),
    buttonPanel(0, 1),
    buttonFit(0, 1) {}
