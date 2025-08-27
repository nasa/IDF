/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SingleRoboticsController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SingleRoboticsController.cpp}
 */

#ifndef SINGLE_ROBOTICS_CONTROLLER_HH
#define SINGLE_ROBOTICS_CONTROLLER_HH

#include "idf/RoboticsController.hh"

#include "idf/Output.hh"
#include "idf/Input.hh"
#include "idf/CompositeInput.hh"

#include "idf/DacoThc.hh"
#include "idf/DualShock.hh"
#include "idf/Extreme3dPro.hh"
#include "idf/GenericJoystick.hh"
#include "idf/Gravis.hh"
#include "idf/Er7Orion.hh"
#include "idf/IndustrialProducts.hh"
#include "idf/IndustrialProducts2.hh"
#include "idf/IndustrialProducts3.hh"
#include "idf/IndustrialProducts4.hh"
#include "idf/SaitekX52.hh"
#include "idf/SaitekX56Stick.hh"
#include "idf/SpaceExplorer.hh"
#include "idf/SpaceNavigator.hh"
#include "idf/SpaceMouse.hh"
#include "idf/ThrustMaster.hh"
#include "idf/ThrustMaster2.hh"
#include "idf/XBoxOne.hh"
#include "idf/VirpilConstellationAlpha.hh"
#include "idf/VirtualLayout.hh"
#include "idf/WingMan.hh"

namespace idf {

/**
 * a single robotics controller.
 *
 * Note: All @c createInstance functions return a controller whose outputs are mapped to the inputs
 * of the specified device following conventional spatial mapping relationships when avaiable and
 * reasonable choices otherwise. The axes follow the right-handed convention and are oriented as follows:
 *
 * +x points forward
 * +y points to the left
 * +z points up
 *
 * positive roll is measured from the +z axis towards the -x axis
 * positive pitch is measured from the +y axis towards the -z axis
 * positive yaw is measured from the +y axis towards the +x axis
 *
 * You may alter the polarity of any axis by inverting the appropriate output. If this orientation is
 * not appropriate for your application, you should use the constructor instead, which allows you to
 * fully customize the mapping.
 *
 * @author Derek Bankieris
 */
class SingleRoboticsController : public RoboticsController {

    public:

    /** roll */
    Output roll;

    /** pitch */
    Output pitch;

    /** yaw */
    Output yaw;

    /** x */
    Output x;

    /** y */
    Output y;

    /** z */
    Output z;

    /** trigger */
    Output trigger;

    /** rate mode */
    Output rateMode;

    /**
     * constructs a new instance using the specified inputs
     *
     * @param roll the input to process as roll
     * @param pitch the input to process as pitch
     * @param yaw the input to process as yaw
     * @param x the input to process as x
     * @param y the input to process as y
     * @param z the input to process as z
     * @param trigger the input to process as trigger
     * @param rateMode the input to process as rate mode
     */
    SingleRoboticsController(
      const Input& roll, const Input& pitch, const Input& yaw,
      const Input& x, const Input& y, const Input& z,
      const Input& trigger, const Input& rateMode);

    /**
     * adds @a deadband to all outputs except #trigger  and #rateMode
     *
     * @param deadband the deadband to add
     */
    void addDeadband(const Deadband& deadband);

    /** removes all deadbands from all outputs */
    void clearDeadbands();

    /**
     * returns the commanded roll, normalized to [-1, 0, 1]
     *
     * @return the roll command
     */
    double getCommandedRoll() const;

    /**
     * returns the commanded pitch, normalized to [-1, 0, 1]
     *
     * @return the pitch command
     */
    double getCommandedPitch() const;

    /**
     * returns the commanded yaw, normalized to [-1, 0, 1]
     *
     * @return the yaw command
     */
    double getCommandedYaw() const;

    /**
     * returns the commanded x, normalized to [-1, 0, 1]
     *
     * @return the x command
     */
    double getCommandedX() const;

    /**
     * returns the commanded y, normalized to [-1, 0, 1]
     *
     * @return the y command
     */
    double getCommandedY() const;

    /**
     * returns the commanded z, normalized to [-1, 0, 1]
     *
     * @return the z command
     */
    double getCommandedZ() const;

    /**
     * returns the commanded trigger
     *
     * @return the trigger command
     */
    bool getCommandedTrigger() const;

    /**
     * returns the commanded rate mode
     *
     * @return the rate mode command
     */
    bool getCommandedRateMode() const;

    /**
     * creates a new SingleRoboticsController mapped to @a wingMan using appropriate defaults
     *
     * @param wingMan the inputs to use in the default mapping
     *
     * @return a new WingMan-based robotics controller
     */
    static SingleRoboticsController* createInstance(const WingMan& wingMan);

    /**
     * creates a new SingleRoboticsController mapped to @a extreme3dPro using appropriate defaults
     *
     * @param extreme3dPro the inputs to use in the default mapping
     *
     * @return a new Extreme3dPro-based robotics controller
     */
    static SingleRoboticsController* createInstance(const Extreme3dPro& extreme3dPro);

    /**
     * creates a new SingleRoboticsController mapped to @a spaceExplorer using appropriate defaults
     *
     * @param spaceExplorer the inputs to use in the default mapping
     *
     * @return a new SpaceExplorer-based robotics controller
     */
    static SingleRoboticsController* createInstance(const SpaceExplorer& spaceExplorer);

    /**
     * creates a new SingleRoboticsController mapped to @a spaceNavigator using appropriate defaults
     *
     * @param spaceNavigator the inputs to use in the default mapping
     *
     * @return a new SpaceNavigator-based robotics controller
     */
    static SingleRoboticsController* createInstance(const SpaceNavigator& spaceNavigator);

    /**
     * creates a new SingleRoboticsController mapped to @a spaceMouse using appropriate defaults
     *
     * @param spaceMouse the inputs to use in the default mapping
     *
     * @return a new SpaceMouse-based robotics controller
     */
    static SingleRoboticsController* createInstance(const SpaceMouse& spaceMouse);

    /**
     * creates a new SingleRoboticsController mapped to @a gravis using appropriate defaults
     *
     * @param gravis the inputs to use in the default mapping
     *
     * @return a new Gravis-based robotics controller
     */
    static SingleRoboticsController* createInstance(const Gravis& gravis);

    /*
     * creates a new SingleRoboticsController mapped to @a dualShock using appropriate defaults
     *
     * @param dualShock the inputs to use in the default mapping
     *
     * @return a new DualShock-based robotics controller
     */
    static SingleRoboticsController* createInstance(const DualShock& dualShock);

    /*
     * creates a new SingleRoboticsController mapped to @a virtualLayout using appropriate defaults
     *
     * @param virtualLayout the inputs to use in the default mapping
     *
     * @return a new VirtualLayout-based robotics controller
     */
    static SingleRoboticsController* createInstance(const VirtualLayout& virtualLayout);

    /*
     * creates a new SingleRoboticsController mapped to @a thrustMaster using appropriate defaults
     *
     * @param thrustMaster the inputs to use in the default mapping
     *
     * @return a new shuttle-style ThrustMaster-based robotics controller
     */
    static SingleRoboticsController* createInstance(const ThrustMaster& thrustMaster);

    /*
     * creates a new SingleRoboticsController mapped to @a thrustMaster2 using appropriate defaults
     *
     * @param thrustMaster2 the inputs to use in the default mapping
     *
     * @return a new Orion-style ThrustMaster-based robotics controller
     */
    static SingleRoboticsController* createInstance(const ThrustMaster2& thrustMaster2);

    /*
     * creates a new SingleRoboticsController mapped to @a XBoxOne using appropriate defaults
     *
     * @param XBoxOne the inputs to use in the default mapping
     *
     * @return a new XBoxOne-based flight controller
     */
    static SingleRoboticsController* createInstance(const XBoxOne& xBoxOne);

    /*
     * creates a new SingleRoboticsController mapped to @a industrialProducts using appropriate defaults
     *
     * @param industrialProducts the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts-based robotics controller
     */
    static SingleRoboticsController* createInstance(const IndustrialProducts& industrialProducts);

    /*
     * creates a new SingleRoboticsController mapped to @a industrialProducts2 using appropriate defaults
     *
     * @param industrialProducts2 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts2-based robotics controller
     */
    static SingleRoboticsController* createInstance(const IndustrialProducts2& industrialProducts2);

    /*
     * creates a new SingleRoboticsController mapped to @a industrialProducts3 using appropriate defaults
     *
     * @param industrialProducts3 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts3-based robotics controller
     */
    static SingleRoboticsController* createInstance(const IndustrialProducts3& industrialProducts3);

    /*
     * creates a new SingleRoboticsController mapped to @a industrialProducts4 using appropriate defaults
     *
     * @param industrialProducts4 the inputs to use in the default mapping
     *
     * @return a new industrialProducts4-based robotics controller
     */
    static SingleRoboticsController* createInstance(const IndustrialProducts4& industrialProducts4);

    /*
     * creates a new SingleRoboticsController mapped to @a SaitekX52 using appropriate defaults
     *
     * @param saitekX52 the inputs to use in the default mapping
     *
     * @return a new SaitekX52-based robotics controller
     */
    static SingleRoboticsController* createInstance(const SaitekX52& saitekX52);

    /*
     * creates a new SingleRoboticsController mapped to @a SaitekX56Stick using appropriate defaults
     *
     * @param saitekX56Stick the inputs to use in the default mapping
     *
     * @return a new SaitekX56Stick-based robotics controller
     */
    static SingleRoboticsController* createInstance(const SaitekX56Stick& saitekX56Stick);

    /*
     * creates a new SingleRoboticsController mapped to @a Er7Orion using appropriate defaults
     *
     * @param Er7Orion the inputs to use in the default mapping
     *
     * @return a new Er7Orion-based flight controller
     */
    static SingleRoboticsController* createInstance(const Er7Orion& er7Orion);


    /**
     * creates a new SingleRoboticsController mapped to @a DacoThc using appropriate defaults
     *
     * @param dacoThc the inputs to use in the default mapping
     *
     * @return a new DacoThc-based camera controller
     */
    static SingleRoboticsController* createInstance(const DacoThc& dacoThc);

    /**
     * creates a new SingleRoboticsController mapped to @a Virpil @a Controls @Constellation @Alpha
     * on a @a MT-50CM3 base using appropriate defaults
     *
     * @param virpil the inputs to use in the default mapping
     *
     * @return a new Virpil Constellation Alhpa based robotics controller
     */
    static SingleRoboticsController* createInstance(const VirpilConstellationAlpha& virpil);

    /**
     * creates a new SingleRoboticsController mapped to @a HidGenericJoystick using appropriate
     * defaults. Since this is a generic mapping without specific knowledge of the
     * devices physical layout, it is merely a best guess according to common practices. Thus,
     * some outputs may not be mapped to an real input.
     *
     * @param js the inputs to use in the default mapping
     *
     * @return a new Generic HID based robotics controller
     */
    static SingleRoboticsController* createInstance(const GenericJoystick& js);
};

}

#endif
