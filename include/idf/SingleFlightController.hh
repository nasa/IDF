/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SingleFlightController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SingleFlightController.cpp}
 */

#ifndef SINGLE_FLIGHT_CONTROLLER_HH
#define SINGLE_FLIGHT_CONTROLLER_HH

#include "idf/FlightController.hh"

#include "idf/Output.hh"
#include "idf/Input.hh"
#include "idf/CompositeInput.hh"

#include "idf/DualShock.hh"
#include "idf/Extreme3dPro.hh"
#include "idf/Gravis.hh"
#include "idf/IndustrialProducts.hh"
#include "idf/IndustrialProducts2.hh"
#include "idf/IndustrialProducts3.hh"
#include "idf/SaitekX52.hh"
#include "idf/SaitekX56Stick.hh"
#include "idf/SpaceBase.hh"
#include "idf/ThrustMasterBase.hh"
#include "idf/VirtualLayout.hh"
#include "idf/WingMan.hh"

namespace idf {

/**
 * a single flight controller.
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
class SingleFlightController : public FlightController {

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

    /**
     * constructs a new instance using the specified inputs
     *
     * @param roll the input to process as roll
     * @param pitch the input to process as pitch
     * @param yaw the input to process as yaw
     * @param x the input to process as x
     * @param y the input to process as y
     * @param z the input to process as z
     */
    SingleFlightController(
      const Input& roll, const Input& pitch, const Input& yaw,
      const Input& x, const Input& y, const Input& z);

    /**
     * adds @a deadband to all outputs
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
     * creates a new SingleFlightController mapped to @a wingMan using appropriate defaults
     *
     * @param wingMan the inputs to use in the default mapping
     *
     * @return a new WingMan-based flight controller
     */
    static SingleFlightController* createInstance(const WingMan& wingMan);

    /**
     * creates a new SingleFlightController mapped to @a extreme3dPro using appropriate defaults
     *
     * @param extreme3dPro the inputs to use in the default mapping
     *
     * @return a new Extreme3dPro-based flight controller
     */
    static SingleFlightController* createInstance(const Extreme3dPro& extreme3dPro);

    /**
     * creates a new SingleFlightController mapped to @a spaceBase using appropriate defaults
     *
     * @param spaceBase the inputs to use in the default mapping
     *
     * @return a new 3dconnexion-based flight controller
     */
    static SingleFlightController* createInstance(const SpaceBase& spaceBase);

    /**
     * creates a new SingleFlightController mapped to @a gravis using appropriate defaults
     *
     * @param gravis the inputs to use in the default mapping
     *
     * @return a new Gravis-based flight controller
     */
    static SingleFlightController* createInstance(const Gravis& gravis);

    /*
     * creates a new SingleFlightController mapped to @a dualShock using appropriate defaults
     *
     * @param dualShock the inputs to use in the default mapping
     *
     * @return a new DualShock-based flight controller
     */
    static SingleFlightController* createInstance(const DualShock& dualShock);

    /*
     * creates a new SingleFlightController mapped to @a virtualLayout using appropriate defaults
     *
     * @param virtualLayout the inputs to use in the default mapping
     *
     * @return a new VirtualLayout-based flight controller
     */
    static SingleFlightController* createInstance(const VirtualLayout& virtualLayout);

    /*
     * creates a new SingleFlightController mapped to @a thrustMaster using appropriate defaults
     *
     * @param thrustMaster the inputs to use in the default mapping
     *
     * @return a new ThrustMaster-based flight controller
     */
    static SingleFlightController* createInstance(const ThrustMasterBase& thrustMaster);

    /*
     * creates a new SingleFlightController mapped to @a industrialProducts using appropriate defaults
     *
     * @param industrialProducts the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts-based flight controller
     */
    static SingleFlightController* createInstance(const IndustrialProducts& industrialProducts);

    /*
     * creates a new SingleFlightController mapped to @a industrialProducts2 using appropriate defaults
     *
     * @param industrialProducts2 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts2-based flight controller
     */
    static SingleFlightController* createInstance(const IndustrialProducts2& industrialProducts2);

    /*
     * creates a new SingleFlightController mapped to @a industrialProducts3 using appropriate defaults
     *
     * @param industrialProducts3 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts3-based flight controller
     */
    static SingleFlightController* createInstance(const IndustrialProducts3& industrialProducts3);

    /**
     * creates a new SingleFlightController mapped to @a SaitekX52 using appropriate defaults
     *
     * @param saitekX52 the inputs to use in the default mapping
     *
     * @return a new SaitekX52-based flight controller
     */
    static SingleFlightController* createInstance(const SaitekX52& saitekX52);

    /**
     * creates a new SingleFlightController mapped to @a SaitekX56Stick using appropriate defaults
     *
     * @param saitekX56Stick the inputs to use in the default mapping
     *
     * @return a new SaitekX56Stick-based flight controller
     */
    static SingleFlightController* createInstance(const SaitekX56Stick& saitekX56Stick);

};

}

#endif
