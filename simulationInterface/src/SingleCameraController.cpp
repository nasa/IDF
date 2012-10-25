#include "SingleCameraController.hh"

using namespace idf;

SingleCameraController::SingleCameraController(
  Input& panInput, Input& tiltInput, Input& spinInput, Input& zoomInput) :
    pan(panInput), tilt(tiltInput), spin(spinInput), zoom(zoomInput) {}

double SingleCameraController::getCommandedPan() {
    return pan.getNormalizedValue();
}

double SingleCameraController::getCommandedTilt() {
    return tilt.getNormalizedValue();
}

double SingleCameraController::getCommandedSpin() {
    return spin.getNormalizedValue();
}

double SingleCameraController::getCommandedZoom() {
    return zoom.getNormalizedValue();
}

SingleCameraController* SingleCameraController::createInstance(WingMan& wingMan) {
    CompositeInput* zoom = new CompositeInput();
    zoom->addInput(wingMan.hatNorth);
    zoom->addInput(wingMan.hatSouth, -1);

    SingleCameraController *wingManSingleCameraController =
      new SingleCameraController(wingMan.twist, wingMan.forwardBackwardPivot,
      wingMan.leftRightPivot, *zoom);

    wingManSingleCameraController->pan.setInverted(true);
    wingManSingleCameraController->tilt.setInverted(true);

    return wingManSingleCameraController;
}

SingleCameraController* SingleCameraController::createInstance(SpaceExplorer& spaceExplorer) {
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

    return spaceExplorerSingleCameraController;
}

SingleCameraController* SingleCameraController::createInstance(SpaceNavigator& spaceNavigator) {
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

    return spaceNavigatorSingleCameraController;
}

SingleCameraController* SingleCameraController::createInstance(Gravis& gravis) {
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

