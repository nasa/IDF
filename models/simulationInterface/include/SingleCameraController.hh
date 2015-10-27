/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((simulationInterface/src/SingleCameraController.cpp))
 */

#ifndef _SINGLE_CAMERA_CONTROLLER_HH_
#define _SINGLE_CAMERA_CONTROLLER_HH_

#include "CameraController.hh"

#include "inputAbstraction/include/Output.hh"
#include "inputAbstraction/include/Input.hh"
#include "inputAbstraction/include/CompositeInput.hh"

#include "inputAbstraction/include/DualShock.hh"
#include "inputAbstraction/include/Extreme3dPro.hh"
#include "inputAbstraction/include/Gravis.hh"
#include "inputAbstraction/include/IndustrialProducts.hh"
#include "inputAbstraction/include/IndustrialProducts2.hh"
#include "inputAbstraction/include/SpaceBase.hh"
#include "inputAbstraction/include/ThrustMasterBase.hh"
#include "inputAbstraction/include/VirtualLayout.hh"
#include "inputAbstraction/include/WingMan.hh"

namespace idf {

/**
 * represents a single camera controller
 *
 * Note: All <code>createInstance</code> functions return a controller whose
 * outputs are mapped to the inputs of the specified device following
 * conventional spatial mapping relationships when avaiable and reasonable
 * choices otherwise. The axes follow the right-handed convention and are
 * oriented as follows:
 *
 * +x points forward
 * +y points to the left
 * +z points up
 *
 * positive roll is measured from the +z axis towards the -x axis
 * positive pitch is measured from the +y axis towards the -z axis
 * positive yaw is measured from the +y axis towards the +x axis
 *
 * You may alter the polarity of any axis by inverting the appropriate output.
 * If this orientation is not appropriate for your application, you should
 * use the constructor instead, which allows you to fully customize the
 * mapping.
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
     * adds <code>deadband</code> to all outputs
     *
     * @param deadband the deadband to add
     */
    void addDeadband(const Deadband& deadband);

    /**
     * removes all deadbands from all outputs
     */
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
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>wingMan</code> using appropriate defaults
     *
     * @param wingMan the inputs to use in the default mapping
     *
     * @return a new WingMan-based camera controller
     */
    static SingleCameraController* createInstance(const WingMan& wingMan);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>extreme3dPro</code> using appropriate defaults
     *
     * @param extreme3dPro the inputs to use in the default mapping
     *
     * @return a new Extreme3dPro-based camera controller
     */
    static SingleCameraController* createInstance(const Extreme3dPro& extreme3dPro);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>spaceExplorer</code> using appropriate defaults
     *
     * @param spaceExplorer the inputs to use in the default mapping
     *
     * @return a new 3dconnexion-based camera controller
     */
    static SingleCameraController* createInstance(const SpaceBase& spaceBase);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>gravis</code> using appropriate defaults
     *
     * @param gravis the inputs to use in the default mapping
     *
     * @return a new Gravis-based camera controller
     */
    static SingleCameraController* createInstance(const Gravis& gravis);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>dualShock</code> using appropriate defaults
     *
     * @param dualShock the inputs to use in the default mapping
     *
     * @return a new DualShock-based camera controller
     */
    static SingleCameraController* createInstance(const DualShock& dualShock);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>virtualLayout</code> using appropriate defaults
     *
     * @param virtualLayout the inputs to use in the default mapping
     *
     * @return a new VirtualLayout-based camera controller
     */
    static SingleCameraController* createInstance(const VirtualLayout& virtualLayout);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>thrustMaster</code> using appropriate defaults
     *
     * @param thrustMaster the inputs to use in the default mapping
     *
     * @return a new ThrustMaster-based camera controller
     */
    static SingleCameraController* createInstance(const ThrustMasterBase& thrustMaster);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>industrialProducts</code> using appropriate defaults
     *
     * @param industrialProducts the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts-based camera controller
     */
    static SingleCameraController* createInstance(const IndustrialProducts& industrialProducts);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>industrialProducts2</code> using appropriate defaults
     *
     * @param industrialProducts2 the inputs to use in the default mapping
     *
     * @return a new IndustrialProducts2-based camera controller
     */
    static SingleCameraController* createInstance(const IndustrialProducts2& industrialProducts2);

};

}

#endif
