/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/DualShock.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/DualShock.cpp}
 */

#ifndef DUAL_SHOCK_HH
#define DUAL_SHOCK_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * base class for Sony DUALSHOCK SIXAXIS game controllers
 *
 * @author Derek Bankieris
 */
class DualShock : public virtual InputLayout {

    public:

    /** enumeration of the rumble packs */
    enum Rumbler {Weak, Strong};

    /** constructor */
    DualShock();

    /** destructor */
    virtual ~DualShock() {};

    /** left analog pad left-right pivot */
    SingleInput leftAnalogLeftRightPivot;

    /** left analog pad up-down pivot */
    SingleInput leftAnalogUpDownPivot;

    /** pushing in of the left analog pad */
    SingleInput leftAnalogIn;

    /** right analog pad left-right pivot */
    SingleInput rightAnalogLeftRightPivot;

    /** right analog pad up-down pivot */
    SingleInput rightAnalogUpDownPivot;

    /** pushing in of the right analog pad */
    SingleInput rightAnalogIn;

    /** up on the directional pad */
    SingleInput directionalPadUp;

    /** down on the directional pad */
    SingleInput directionalPadDown;

    /** left on the directional pad */
    SingleInput directionalPadLeft;

    /** right on the directional pad */
    SingleInput directionalPadRight;

    /** the button labeled with a sqaure */
    SingleInput squareButton;

    /** the button labeled with a triangle */
    SingleInput triangleButton;

    /** the button labeled with an X */
    SingleInput xButton;

    /** the button labeled with a circle */
    SingleInput circleButton;

    /** the PS (PlayStation) button located bewteen the two analog sticks */
    SingleInput psButton;

    /** the button labeled L1 */
    SingleInput leftBumper;

    /** the button labeled R1 */
    SingleInput rightBumper;

    /** the button labeled L2 */
    SingleInput leftTrigger;

    /** the button labeled R2 */
    SingleInput rightTrigger;

    /**
     * rumbles the specified @a rumbler
     *
     * @param rumbler the rumbler to rumble
     * @param intensity the intensity of the rumble. 0 = off, 255 = maximum
     */
    virtual void rumble(Rumbler rumbler, unsigned char intensity) = 0;

    /** stops all vibration */
    virtual void silenceRumblers();

    protected:

    /**
     * sends the rumble and LED command packet
     *
     * Quirks<br>
     * The sixaxis has both a control endpoint and an interrupt out endpoint.
     * In such a case, output reports would normally be sent over the interrupt
     * out endpoint. However, the sixaxis accepts output reports ONLY on the
     * control endpoint, and silently discards those arriving on the interrupt
     * out endpoint. Thus, the effectiveness of this function depends on the OS
     * libraries having patches to support the sixaxis's unique behavior.
     */
    virtual void sendCommand() = 0;

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
