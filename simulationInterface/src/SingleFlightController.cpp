#include "SingleFlightController.hh"

using namespace idf;

SingleFlightController::SingleFlightController(
  Input& rollInput, Input& pitchInput, Input& yawInput,
  Input& xInput, Input& yInput, Input& zInput) :
    roll(rollInput), pitch(pitchInput), yaw(yawInput),
    x(xInput), y(yInput), z(zInput) {}

double SingleFlightController::getRoll() {
    return roll.getValue();
}

double SingleFlightController::getPitch() {
    return pitch.getValue();
}

double SingleFlightController::getYaw() {
    return yaw.getValue();
}

double SingleFlightController::getX() {
    return x.getValue();
}

double SingleFlightController::getY() {
    return y.getValue();
}

double SingleFlightController::getZ() {
    return z.getValue();
}

SingleFlightController* SingleFlightController::createInstance(WingMan& wingMan) {
    CompositeInput* x = new CompositeInput();
    x->addInput(wingMan.hatNorth);
    x->addInput(wingMan.hatSouth, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(wingMan.hatWest);
    y->addInput(wingMan.hatEast, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(wingMan.button4);
    z->addInput(wingMan.button5, -1);

    SingleFlightController *wingManSingleFlightController =
      new SingleFlightController(wingMan.leftRightPivot,
      wingMan.forwardBackwardPivot, wingMan.twist, *x, *y, *z);

    wingManSingleFlightController->pitch.setInverted(true);
    wingManSingleFlightController->yaw.setInverted(true);

    return wingManSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(SpaceExplorer& spaceExplorer) {
    SingleFlightController *spaceExplorerSingleFlightController =
      new SingleFlightController(
      spaceExplorer.leftRightPivot,
      spaceExplorer.forwardBackwardPivot,
      spaceExplorer.twist,
      spaceExplorer.forwardBackwardTranslation,
      spaceExplorer.leftRightTranslation,
      spaceExplorer.upDownTranslation);

    spaceExplorerSingleFlightController->x.setInverted(true);
    spaceExplorerSingleFlightController->y.setInverted(true);
    spaceExplorerSingleFlightController->z.setInverted(true);
    spaceExplorerSingleFlightController->roll.setInverted(true);
    spaceExplorerSingleFlightController->pitch.setInverted(true);
    spaceExplorerSingleFlightController->yaw.setInverted(true);

    return spaceExplorerSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(SpaceNavigator& spaceNavigator) {
    SingleFlightController *spaceNavigatorSingleFlightController =
      new SingleFlightController(
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardTranslation,
      spaceNavigator.leftRightTranslation,
      spaceNavigator.upDownTranslation);

    spaceNavigatorSingleFlightController->x.setInverted(true);
    spaceNavigatorSingleFlightController->y.setInverted(true);
    spaceNavigatorSingleFlightController->z.setInverted(true);
    spaceNavigatorSingleFlightController->roll.setInverted(true);
    spaceNavigatorSingleFlightController->pitch.setInverted(true);
    spaceNavigatorSingleFlightController->yaw.setInverted(true);

    return spaceNavigatorSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(Gravis& gravis) {
    CompositeInput* roll = new CompositeInput();
    roll->addInput(gravis.rightBumper2);
    roll->addInput(gravis.leftBumper2, -1);

    CompositeInput* pitch = new CompositeInput();
    pitch->addInput(gravis.eastButton);
    pitch->addInput(gravis.northButton, -1);

    CompositeInput* yaw = new CompositeInput();
    yaw->addInput(gravis.leftBumper1);
    yaw->addInput(gravis.rightBumper1, -1);

    CompositeInput* x = new CompositeInput();
    x->addInput(gravis.westButton);
    x->addInput(gravis.southButton, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(gravis.directionalPadLeft);
    y->addInput(gravis.directionalPadRight, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(gravis.directionalPadUp);
    z->addInput(gravis.directionalPadDown, -1);

    return new SingleFlightController(*roll, *pitch, *yaw, *x, *y, *z);
}
