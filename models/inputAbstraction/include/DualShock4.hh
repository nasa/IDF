/**
 * @trick_parse{everything}
 * @trick_link_dependency{inputAbstraction/src/DualShock4.cpp}
 */

#ifndef DUAL_SHOCK_4_HH
#define DUAL_SHOCK_4_HH

#include "inputAbstraction/include/DualShock.hh"
#include "inputAbstraction/include/SingleInput.hh"

namespace idf {

/**
 * Sony DUALSHOCK4 SIXAXIS game controller's input layout
 *
 * @author Derek Bankieris
 */
class DualShock4 : public virtual DualShock {

    public:

    #ifndef SWIG
    /** the %trackpad */
    class Trackpad {

        public:

        /** position on the trackpad */
        class Finger {

            public:

            /** constructor */
            Finger();

            /** finger in contact with trackpad (boolean) */
            SingleInput contact;

            /** x position */
            SingleInput x;

            /** y position */
            SingleInput y;

        };

        /** constructor */
        Trackpad();

        /** the trackpad itself is a pressable button */
        SingleInput button;

        /** the first finger down */
        Finger finger1;

        /** the second finger down */
        Finger finger2;

    };
    #endif

    /** constructor */
    DualShock4();

    /** destructor */
    virtual ~DualShock4() {};

    /** the button labeled share */
    SingleInput shareButton;

    /** the button labeled options */
    SingleInput optionsButton;

    #ifndef SWIG
    /** the trackpad */
    Trackpad trackpad;
    #endif

    void rumble(Rumbler rumbler, unsigned char data);

    /**
     * sets the light bar's color
     *
     * @param red the red value
     * @param green the green value
     * @param blue the blue value
     */
    virtual void setLightBarColor(unsigned char red, unsigned char green, unsigned char blue);

    /**
     * sets the light bar's on/off cycle
     *
     * @param on duration of the on portion (in hundredths of a second)
     * @param off duration of the off portion (in hundredths of a second)
     */
    virtual void setLightBarCycle(unsigned char on, unsigned char off);

    protected:

    /**
     *     0 = 0x11 for bluetooth; 0x05 for USB (with all other indicies reduced by 2)
     *   1-2 = unknown
     *     3 = 0xf0 (disable motors) | 0xf3 (enable motors)
     *   4-5 = unknown
     *     6 = weak rumble
     *     7 = strong rumble
     *     8 = red
     *     9 = green
     *    10 = blue
     * 11-73 = unknown
     * 74-77 = CRC-32
     */
    unsigned char command[78];

};

}

#endif
