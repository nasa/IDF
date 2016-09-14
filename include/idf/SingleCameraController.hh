/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/SingleCameraController.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/SingleCameraController.cpp}
 */

#ifndef SINGLE_CAMERA_CONTROLLER_HH
#define SINGLE_CAMERA_CONTROLLER_HH

#include "idf/CameraController.hh"

#include "idf/Output.hh"
#include "idf/Input.hh"
#include "idf/CompositeInput.hh"

#include "idf/DualShock.hh"
#include "idf/Extreme3dPro.hh"
#include "idf/Gravis.hh"
#include "idf/IndustrialProducts.hh"
#include "idf/IndustrialProducts2.hh"
#include "idf/SpaceBase.hh"
#include "idf/ThrustMasterBase.hh"
#include "idf/VirtualLayout.hh"
#include "idf/WingMan.hh"

namespace idf {

/**
 * a single camera controller.
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
class SingleCameraController : public CameraController {

    public:

    /** pan */
    Output pan;

    /** tilt */
    Output tilt;

    /** spin */
    Output spin;

    /** zoom */
    Output zoom;

    /**
     * constructs a new instance using the specified inputs
     *
     * @param pan the input to process as pan
     * @param tilt the input to process as tilt
     * @param spin the input to process as spin
     * @param zoom the input to process as zoom
     */
    SingleCameraController(const Input& pan, const Input& tilt, const Input& spin, const Input& zoom);

    /**
     * adds @a deadband to all outputs
     *
     * @param deadband the deadband to add
     */
    void addDeadband(const Deadband& deadband);

    /** removes all deadbands from all outputs */
    void clearDeadbands();

    /**
     * returns the commanded pan, normalized to [-1, 0, 1]
     *
     * @return the pan command
     */
    double getCommandedPan() const;

    /**
     * returns the commanded tilt, normalized to [-1, 0, 1]
     *
     * @return the tilt command
     */
    double getCommandedTilt() const;

    /**
     * returns the commanded spin, normalized to [-1, 0, 1]
     *
     * @return the spin command
     */
    double getCommandedSpin() const;

    /**
     * returns the commanded zoom, normalized to [-1, 0, 1]
     *
     * @return the zoom command
     */
    double getCommandedZoom() const;

    /**
     * creates a new SingleCameraController mapped to @a wingMan using appropriate defaults
     *
     * @param wingMan the inputs to use in the default mapping
     *
     * @return a new WingMan-based camera controller
     */
    static SingleCameraController* createInstance(const WingMan& wingMan);

    /**
     * creates a new SingleCameraController mapped to @a extreme3dPro using appropriate defaults
     *
     * @param extreme3dPro the inputs to use in the default mapping
     *
     * @return a new Extreme3dPro-based camera controller
     */
    static SingleCameraController* createInstance(const Extreme3dPro& extreme3dPro);

    /**
     * creates a new SingleCameraController mapped to @a spaceBase using appropriate defaults
     *
     * @param spaceBase the inputs to use in the default mapping
     *
     * @return a new 3dconnexion-based camera controller
     */
    static SingleCameraController* createInstance(const SpaceBase& spaceBase);

    /**
     * creates a new SingleCameraController mapped to @a gravis using appropriate defaults
     *
     * @param gravis the inputs to use in the default mapping
     *
     * @return a new Gravis-based camera controller
     */
    static SingleCameraController* createInstance(const Gravis& gravis);

    /**
     * creates a new SingleCameraController mapped to @a dualShock using appropriate defaults
     *
     * @param dualShock the inputs to use in the default mapping
     *
     * @return a new DualShock-based camera controller
     */
    static SingleCameraController* createInstance(const DualShock& dualShock);

    /**
     * creates a new SingleCameraController mapped to @a virtualLayout using appropriate defaults
     *
     * @param virtualLayout the inputs to use in the default mapping
     *
     * @return a new VirtualLayout-based camera controller
     */
    static SingleCameraController* createInstance(const VirtualLayout& virtualLayout);

    /**
     * creates a new SingleCameraController mapped to @a thrustMaster using appropriate defaults
     *
     * @param thrustMaster the inputs to use in the default mapping
     *
     * @return a new ThrustMaster-based camera controller
     */
    static SingleCameraController* createInstance(const ThrustMasterBase& thrustMaster);

    /**
     * creates a new SingleCameraController mapped to @a industrialProducts using appropriate defaults
     *
     * @param industrialProducts the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts-based camera controller
     */
    static SingleCameraController* createInstance(const IndustrialProducts& industrialProducts);

    /**
     * creates a new SingleCameraController mapped to @a industrialProducts2 using appropriate defaults
     *
     * @param industrialProducts2 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts2-based camera controller
     */
    static SingleCameraController* createInstance(const IndustrialProducts2& industrialProducts2);

};

}

#endif
