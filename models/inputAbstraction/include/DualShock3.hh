/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((inputAbstraction/src/DualShock3.cpp))
 */

#ifndef _DUAL_SHOCK_3_HH_
#define _DUAL_SHOCK_3_HH_

#include "SingleInput.hh"

namespace idf {

/**
 * represents a Sony DUALSHOCK3 SIXAXIS hand controller's input layout
 *
 * @author Derek Bankieris
 */
class DualShock3 {

    public:

    /** enumeration of the rumble packs */
    enum Rumbler {HighFrequency, LowFrequency};

    /** enumeration of the LEDs */
    enum LED {One = 3, Two = 2, Three = 1, Four = 0};

    /** constructor */
    DualShock3();

    /** destructor */
    virtual ~DualShock3() {};

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

    /** the button labeled select */
    SingleInput selectButton;

    /** the center PlayStation button */
    SingleInput playStationButton;

    /** the button labeled start */
    SingleInput startButton;

    /** the button labeled with a sqaure */
    SingleInput squareButton;

    /** the button labeled with a triangle */
    SingleInput triangleButton;

    /** the button labeled with an X */
    SingleInput xButton;

    /** the button labeled with a circle */
    SingleInput circleButton;

    /** the button labeled 1 above the side labeled L */
    SingleInput leftBumper;

    /** the button labeled 1 above the side labeled R*/
    SingleInput rightBumper;

    /** the button labeled 2 above the side labeled L */
    SingleInput leftTrigger;

    /** the button labeled 2 above the side labeled R */
    SingleInput rightTrigger;

    /**
     * sets the portion of the command packet that corresponds to <code>rumbler</code>
     *
     * @param the rumble pack to command
     * @param duration the length of the vibration in units of 20 ms. 0 = off, 255 = infinite
     * @param intensity the magnitude of the vibration. 0 = off, 255 = maximum
     */
    virtual void setRumbleCommand(Rumbler rumbler, unsigned char duration, unsigned char intensity);

    /**
     * sets the portion of the command packet that corresponds to
     * <code>led</code>. The total cycle period is equal to
     * <code>cyclePeriodInteger + cyclePeriodFraction / 256</code>. The actual
     * on/off time is some combination of the total cycle period and the on and
     * off factors, but documentation is sparse.
     *
     * @param led the led to command
     * @param commandDuration the length of time, in units of 20 ms, that the
     * command is valid, after which the LED turns off. 255 = infinite
     * @param cyclePeriodInteger the integer portion of the cycle period
     * @param cyclePeriodFraction the fractional portion of the cycle period in
     * increments of 1 / 256
     * @param offFactor multipled by the cycle period to determine how long the
     * LED is off per cycle
     * @param onFactor multipled by the cycle period to determine how long the
     * LED is on per cycle
     */
    virtual void setLedCommand(LED led, unsigned char commandDuration,
      unsigned char cyclePeriodInteger, unsigned char cyclePeriodFraction,
      unsigned char offFactor, unsigned char onFactor);

    /**
     * sends the rumble pack and LED command packet.
     *
     * Quirks
     * The sixaxis has both a control endpoint and an interrupt out endpoint.
     * In such a case, output reports would normally be sent over the interrupt
     * out endpoint. However, the sixaxis accepts output reports ONLY on the
     * control endpoint, and silently discards those arriving on the interrupt
     * out endpoint. Thus, the effectiveness of this function depends on the OS
     * libraries (hidraw for Linux and the IOKit framework on Mac) having
     * patches to support the sixaxis' unique behavior. Similarly, patches may
     * be required to support communication via Bluetooth as well.
     */
    virtual void sendCommand() = 0;

    protected:

    /**
     * rumble & LED command packet
     *
     * Rumble Pack Bytes
     * report number: always 1
     * |     duration of weak (right) rumble, units = 20 ms, 0xff = infinity
     * |     |     magnitude of weak (right) rumble
     * |     |     |     duration of strong (left) rumble, units = 20 ms, 0xff = infinity
     * |     |     |     |     magnitude of strong (left) rumble
     * |     |     |     |     |
     * 0x01, 0xfe, 0xff, 0xfe, 0xff
     *
     * LED Bytes
     * the total time this command is applied, after which the LED turns off, units = 20 ms, 0xff = infinity
     * |     integer part of the cycle period
     * |     |     fractional part of the cycle period in increments of 1 / 256
     * |     |     |     multiplied by the cycle period to determine how long the LED is off per cycle
     * |     |     |     |     multiplied by the cycle period to determine how long the LED is on per cycle
     * |     |     |     |     |
     * 0xff, 0x27, 0x10, 0x32, 0x32
     *
     * Command Packet Bytes
     *   0 - 4 = rumble pack parameters
     *   5 - 8 = unused
     *       9 = bitwise OR of LEDs to be powered. LED1 = 2, LED2 = 4, LED3 = 8, LED4 = 16
     * 10 - 14 = LED4 parameters
     * 15 - 19 = LED3 parameters
     * 20 - 24 = LED2 parameters
     * 25 - 29 = LED1 parameters
     *
     * Per LED, a command different from it's current state takes effect immediately. Commands that do not
     * change the state are ignored, and will not "reset" the LED's cycle. LEDs start their cycle in the off
     * stage. Both rumble pack and all LED commands are initially zero.
     */
    unsigned char command[30];

};

}

#endif
