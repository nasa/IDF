#include "SingleCameraController.hh"

using namespace idf;

SingleCameraController::SingleCameraController(
  const Input& panInput, const Input& tiltInput, const Input& spinInput, const Input& zoomInput) :
    pan(panInput), tilt(tiltInput), spin(spinInput), zoom(zoomInput) {}

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

    SingleCameraController *wingManSingleCameraController =
      new SingleCameraController(wingMan.twist, wingMan.forwardBackwardPivot,
      wingMan.leftRightPivot, *zoom);

    wingManSingleCameraController->pan.setInverted(true);
    wingManSingleCameraController->tilt.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    wingManSingleCameraController->pan.addDeadband(*deadband);
    wingManSingleCameraController->tilt.addDeadband(*deadband);
    wingManSingleCameraController->spin.addDeadband(*deadband);

    return wingManSingleCameraController;
}

SingleCameraController* SingleCameraController::createInstance(const SpaceExplorer& spaceExplorer) {
    SingleCameraController *spaceExplorerSingleCameraController =
      new SingleCameraController(
      spaceExplorer.twist,
      spaceExplorer.forwardBackwardPivot,
      spaceExplorer.leftRightPivot,
      spaceExplorer.forwardBackwardTranslation);

    spaceExplorerSingleCameraController->pan.setInverted(true);
    spaceExplorerSingleCameraController->tilt.setInverted(true);
    spaceExplorerSingleCameraController->spin.setInverted(true);
    spaceExplorerSingleCameraController->zoom.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    spaceExplorerSingleCameraController->pan.addDeadband(*deadband);
    spaceExplorerSingleCameraController->tilt.addDeadband(*deadband);
    spaceExplorerSingleCameraController->spin.addDeadband(*deadband);

    return spaceExplorerSingleCameraController;
}

SingleCameraController* SingleCameraController::createInstance(const SpaceNavigator& spaceNavigator) {
    SingleCameraController *spaceNavigatorSingleCameraController =
      new SingleCameraController(
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardTranslation);

    spaceNavigatorSingleCameraController->pan.setInverted(true);
    spaceNavigatorSingleCameraController->tilt.setInverted(true);
    spaceNavigatorSingleCameraController->spin.setInverted(true);
    spaceNavigatorSingleCameraController->zoom.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    spaceNavigatorSingleCameraController->pan.addDeadband(*deadband);
    spaceNavigatorSingleCameraController->tilt.addDeadband(*deadband);
    spaceNavigatorSingleCameraController->spin.addDeadband(*deadband);

    return spaceNavigatorSingleCameraController;
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

SingleCameraController* SingleCameraController::createInstance(const DualShock3& dualShock3) {
    CompositeInput* pan = new CompositeInput();
    pan->addInput(dualShock3.directionalPadLeft);
    pan->addInput(dualShock3.directionalPadRight, -1);

    CompositeInput* tilt = new CompositeInput();
    tilt->addInput(dualShock3.directionalPadUp, -1);
    tilt->addInput(dualShock3.directionalPadDown);

    CompositeInput* spin = new CompositeInput();
    spin->addInput(dualShock3.leftBumper, -1);
    spin->addInput(dualShock3.rightBumper);

    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(dualShock3.circleButton);
    zoom->addInput(dualShock3.squareButton, -1);

    return new SingleCameraController(*pan, *tilt, *spin, *zoom);
}

SingleCameraController* SingleCameraController::createInstance(const VirtualLayout& virtualLayout) {
    return new SingleCameraController(
      virtualLayout.leftRightRotation,
      virtualLayout.upDownRotation,
      virtualLayout.clockwiseCounterclockwiseRotation,
      virtualLayout.inOutTranslation);
}

SingleCameraController* SingleCameraController::createInstance(const ThrustMaster& thrustMaster) {
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
