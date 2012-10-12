#ifndef _CAMERA_CONTROLLER_HH_
#define _CAMERA_CONTROLLER_HH_

namespace hardware {

/**
 * represents the interface that an input device must satisfy to qualify as a
 * camera controller device
 *
 * @author Derek Bankieris
 */
class CameraController {

    public:

    virtual ~CameraController() {};

    virtual double getPan() = 0;
    virtual double getTilt() = 0;
    virtual double getSpin() = 0;
    virtual double getZoom() = 0;

};

}

#endif
