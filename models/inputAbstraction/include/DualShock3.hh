/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/DualShock3.cpp}
 */

#ifndef DUAL_SHOCK_3_HH
#define DUAL_SHOCK_3_HH

#include "inputAbstraction/include/DualShock.hh"
#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * represents a Sony DUALSHOCK3 SIXAXIS game controller's input layout
 *
 * @author Derek Bankieris
 */
class DualShock3 : public virtual DualShock {

    public:

    /** enumeration of the LEDs */
    enum LED {One = 3, Two = 2, Three = 1, Four = 0};

    /** constructor */
    DualShock3();

    /** destructor */
    virtual ~DualShock3() {};

    /** the button labeled select */
    SingleInput selectButton;

    /** the button labeled start */
    SingleInput startButton;

    void rumble(Rumbler rumbler, unsigned char data);

    /**
     * sets the portion of the command packet that corresponds to @a rumbler
     *
     * @param rumbler the rumble pack to command
     * @param duration the length of the vibration in units of 20 ms. 0 = off, 255 = infinite
     * @param intensity the magnitude of the vibration. 0 = off, 255 = maximum
     */
    virtual void rumble(Rumbler rumbler, unsigned char duration, unsigned char intensity);

    /**
     * sets the specified @a led. The total cycle period is equal to
     * <code>cyclePeriodInteger + cyclePeriodFraction / 256</code>. The actual
     * on/off time is some combination of the total cycle period and the on and
     * off factors, but documentation is sparse.
     *
     * @param led the led to command
     * @param commandDuration the length of time, in units of 20 ms, that the
     *        command is valid, after which the LED turns off. 255 = infinite
     * @param cyclePeriodInteger the integer portion of the cycle period
     * @param cyclePeriodFraction the fractional portion of the cycle period in increments of 1 / 256
     * @param offFactor multipled by the cycle period to determine how long the LED is off per cycle
     * @param onFactor multipled by the cycle period to determine how long the LED is on per cycle
     */
    virtual void setLed(LED led, unsigned char commandDuration,
      unsigned char cyclePeriodInteger, unsigned char cyclePeriodFraction,
      unsigned char offFactor, unsigned char onFactor);

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

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
