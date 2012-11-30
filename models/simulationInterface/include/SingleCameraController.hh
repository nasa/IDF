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
#include "inputAbstraction/include/WingMan.hh"
#include "inputAbstraction/include/SpaceExplorer.hh"
#include "inputAbstraction/include/SpaceNavigator.hh"
#include "inputAbstraction/include/Gravis.hh"
#include "inputAbstraction/include/DualShock3.hh"

namespace idf {

/**
 * represents a single camera controller
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

    /** destructor */
    virtual ~SingleCameraController() {};

    /**
     * returns the commanded pan, normalized to [-1, 0, 1]
     *
     * @return the pan command
     */
    virtual double getCommandedPan() const;

    /**
     * returns the commanded tilt, normalized to [-1, 0, 1]
     *
     * @return the tilt command
     */
    virtual double getCommandedTilt() const;

    /**
     * returns the commanded spin, normalized to [-1, 0, 1]
     *
     * @return the spin command
     */
    virtual double getCommandedSpin() const;

    /**
     * returns the commanded zoom, normalized to [-1, 0, 1]
     *
     * @return the zoom command
     */
    virtual double getCommandedZoom() const;

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
     * <code>spaceExplorer</code> using appropriate defaults
     *
     * @param spaceExplorer the inputs to use in the default mapping
     *
     * @return a new SpaceExplorer-based camera controller
     */
    static SingleCameraController* createInstance(const SpaceExplorer& spaceExplorer);

    /**
     * creates a new <code>SingleCameraController</code> mapped to
     * <code>spaceNavigator</code> using appropriate defaults
     *
     * @param spaceNavigator the inputs to use in the default mapping
     *
     * @return a new SpaceNavigator-based camera controller
     */
    static SingleCameraController* createInstance(const SpaceNavigator& spaceNavigator);

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
     * <code>dualShock3</code> using appropriate defaults
     *
     * @param dualShock3 the inputs to use in the default mapping
     *
     * @return a new DualShock3-based camera controller
     */
    static SingleCameraController* createInstance(const DualShock3& dualShock3);

};

}

#endif
