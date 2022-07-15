#include "idf/SingleCameraController.hh"

namespace idf {

SingleCameraController::SingleCameraController(
  const Input& panInput, const Input& tiltInput, const Input& spinInput, const Input& zoomInput) :
    pan(panInput), tilt(tiltInput), spin(spinInput), zoom(zoomInput) {}

void SingleCameraController::addDeadband(const Deadband& deadband) {
    pan.addDeadband(deadband);
    tilt.addDeadband(deadband);
    spin.addDeadband(deadband);
    zoom.addDeadband(deadband);
}

void SingleCameraController::clearDeadbands() {
    pan.clearDeadbands();
    tilt.clearDeadbands();
    spin.clearDeadbands();
    zoom.clearDeadbands();
}

double SingleCameraController::getCommandedPan() const {
    return pan.getNormalizedValue();
}

double SingleCameraController::getCommandedTilt() const {
    return tilt.getNormalizedValue();
}

double SingleCameraController::getCommandedSpin() const {
    return spin.getNormalizedValue();
}

double SingleCameraController::getCommandedZoom() const {
    return zoom.getNormalizedValue();
}

SingleCameraController* SingleCameraController::createInstance(const WingMan& wingMan) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(wingMan.hatNorth);
    zoom->addInput(wingMan.hatSouth, -1);

    SingleCameraController *controller =
      new SingleCameraController(wingMan.twist, wingMan.forwardBackwardPivot,
      wingMan.leftRightPivot, *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const Extreme3dPro& extreme3dPro) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(extreme3dPro.hatNorth);
    zoom->addInput(extreme3dPro.hatSouth, -1);

    SingleCameraController *controller =
      new SingleCameraController(extreme3dPro.twist, extreme3dPro.forwardBackwardPivot,
      extreme3dPro.leftRightPivot, *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const SpaceBase& spaceBase) {
    SingleCameraController *controller =
      new SingleCameraController(
      spaceBase.twist,
      spaceBase.forwardBackwardPivot,
      spaceBase.leftRightPivot,
      spaceBase.forwardBackwardTranslation);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);
    controller->spin.setInverted(true);
    controller->zoom.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const Gravis& gravis) {
    CompositeInput* pan = new CompositeInput();
    pan->addInput(gravis.directionalPadLeft);
    pan->addInput(gravis.directionalPadRight, -1);

    CompositeInput* tilt = new CompositeInput();
    tilt->addInput(gravis.directionalPadUp);
    tilt->addInput(gravis.directionalPadDown, -1);

    CompositeInput* spin = new CompositeInput();
    spin->addInput(gravis.leftBumper1);
    spin->addInput(gravis.rightBumper1, -1);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(gravis.westButton);
    zoom->addInput(gravis.southButton, -1);

    return new SingleCameraController(*pan, *tilt, *spin, *zoom);
}

SingleCameraController* SingleCameraController::createInstance(const DualShock& dualShock) {
    CompositeInput* pan = new CompositeInput();
    pan->addInput(dualShock.directionalPadLeft);
    pan->addInput(dualShock.directionalPadRight, -1);

    CompositeInput* tilt = new CompositeInput();
    tilt->addInput(dualShock.directionalPadUp, -1);
    tilt->addInput(dualShock.directionalPadDown);

    CompositeInput* spin = new CompositeInput();
    spin->addInput(dualShock.leftBumper, -1);
    spin->addInput(dualShock.rightBumper);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(dualShock.circleButton);
    zoom->addInput(dualShock.squareButton, -1);

    SingleCameraController* controller = new SingleCameraController(*pan, *tilt, *spin, *zoom);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const VirtualLayout& virtualLayout) {
    return new SingleCameraController(
      virtualLayout.leftRightRotation,
      virtualLayout.upDownRotation,
      virtualLayout.clockwiseCounterclockwiseRotation,
      virtualLayout.inOutTranslation);
}

SingleCameraController* SingleCameraController::createInstance(const ThrustMasterBase& thrustMaster) {
    SingleCameraController *controller =
      new SingleCameraController(
      thrustMaster.twist,
      thrustMaster.forwardBackwardPivot,
      thrustMaster.leftRightPivot,
      thrustMaster.forwardBackwardTranslation);

    controller->tilt.setInverted(true);
    controller->pan.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const IndustrialProducts& industrialProducts) {
    SingleCameraController *controller =
      new SingleCameraController(
      industrialProducts.twist,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.leftRightPivot,
      industrialProducts.hatUpDownPivot);

    controller->pan.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const IndustrialProducts2& industrialProducts2) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(industrialProducts2.hatNorth);
    zoom->addInput(industrialProducts2.hatSouth, -1);

    SingleCameraController *controller =
      new SingleCameraController(
      industrialProducts2.twist,
      industrialProducts2.forwardBackwardPivot,
      industrialProducts2.leftRightPivot,
      *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const IndustrialProducts3& industrialProducts) {
    SingleCameraController *controller =
      new SingleCameraController(
      industrialProducts.twist,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.leftRightPivot,
      industrialProducts.hatUpDownPivot);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}

SingleCameraController* SingleCameraController::createInstance(const SaitekX52& saitekX52) {
    CompositeInput* spin = new CompositeInput();
    spin->addInput(saitekX52.toggle1);
    spin->addInput(saitekX52.toggle2, -1);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(saitekX52.mode3, 1);
    zoom->addInput(saitekX52.mode1, -1);

    SingleCameraController *controller =
      new SingleCameraController(
        saitekX52.hat1LeftRightPivot,
        saitekX52.hat1UpDownPivot,
        *spin,
        *zoom);

    controller->pan.setInverted(true);
    controller->tilt.setInverted(true);

    return controller;
}


}
