/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Teensyduino.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Teensyduino.cpp}
 */

#ifndef TEENSYDUINO_HH
#define TEENSYDUINO_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Teensyduino Joystick
 *
 * @author Philip Kunz
 */
class Teensyduino : public virtual InputLayout {

    public:

    /** constructor */
    Teensyduino();

    /** destructor */
    virtual ~Teensyduino() {};

    /** buttons */
    SingleInput button1;
    SingleInput button2;
    SingleInput button3;
    SingleInput button4;
    SingleInput button5;
    SingleInput button6;
    SingleInput button7;
    SingleInput button8;
    SingleInput button9;
    SingleInput button10;
    SingleInput button11;
    SingleInput button12;
    SingleInput button13;
    SingleInput button14;
    SingleInput button15;
    SingleInput button16;
    SingleInput button17;
    SingleInput button18;
    SingleInput button19;
    SingleInput button20;
    SingleInput button21;
    SingleInput button22;
    SingleInput button23;
    SingleInput button24;
    SingleInput button25;
    SingleInput button26;
    SingleInput button27;
    SingleInput button28;
    SingleInput button29;
    SingleInput button30;
    SingleInput button31;
    SingleInput button32;

    /** Axes */
    SingleInput x;
    SingleInput y;
    SingleInput z;
    SingleInput zRotate;

    /* sliders  */
    SingleInput sliderLeft;
    SingleInput sliderRight;

    /** hat1 directions */
    SingleInput hatNorth;
    SingleInput hatNorthEast;
    SingleInput hatEast;
    SingleInput hatSouthEast;
    SingleInput hatSouth;
    SingleInput hatSouthWest;
    SingleInput hatWest;
    SingleInput hatNorthWest;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
