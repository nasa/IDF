/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/DualShock4.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/DualSense.cpp}
 */

 #ifndef DUAL_SENSE_HH
 #define DUAL_SENSE_HH

 #include "idf/DualShock4.hh"

namespace idf {

/**
 * Sony Playstation 5 DualSense controller
 */
class DualSense : public virtual DualShock4 {

    public:

    DualSense();

    virtual ~DualSense() {};

    /** L2 Discrete */
    SingleInput  leftTriggerDiscrete;

    /** R2 Discrete */
    SingleInput  rightTriggerDiscrete;

    /** Mic Mute Button */
    SingleInput mute;

    /** Motion Angular Velocity X */
    SingleInput anglularVelocityX;

    /** Motion Angular Velocity Y */
    SingleInput anglularVelocityY;

    /** Motion Angular Velocity Z */
    SingleInput anglularVelocityZ;

    /** Motion Acceleration X */
    SingleInput accelerationX;

    /** Motion Acceleration Y */
    SingleInput accelerationY;

    /** Motion Acceleration Z */
    SingleInput accelerationZ;

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

    virtual const std::vector<Configurable>& getConfigurables();

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



} // namespace

#endif