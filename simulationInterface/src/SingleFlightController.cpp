#include "SingleFlightController.hh"

using namespace idf;

SingleFlightController::SingleFlightController(
  const Input& rollInput, const Input& pitchInput, const Input& yawInput,
  const Input& xInput, const Input& yInput, const Input& zInput) :
    roll(rollInput), pitch(pitchInput), yaw(yawInput),
    x(xInput), y(yInput), z(zInput) {}

double SingleFlightController::getCommandedRoll() const {
    return roll.getNormalizedValue();
}

double SingleFlightController::getCommandedPitch() const {
    return pitch.getNormalizedValue();
}

double SingleFlightController::getCommandedYaw() const {
    return yaw.getNormalizedValue();
}

double SingleFlightController::getCommandedX() const {
    return x.getNormalizedValue();
}

double SingleFlightController::getCommandedY() const {
    return y.getNormalizedValue();
}

double SingleFlightController::getCommandedZ() const {
    return z.getNormalizedValue();
}

SingleFlightController* SingleFlightController::createInstance(const WingMan& wingMan) {
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

    Deadband *deadband = new Deadband(-0.05, 0.05);
    wingManSingleFlightController->roll.addDeadband(*deadband);
    wingManSingleFlightController->pitch.addDeadband(*deadband);
    wingManSingleFlightController->yaw.addDeadband(*deadband);

    return wingManSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(const SpaceExplorer& spaceExplorer) {
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

    Deadband *deadband = new Deadband(-0.05, 0.05);
    spaceExplorerSingleFlightController->roll.addDeadband(*deadband);
    spaceExplorerSingleFlightController->pitch.addDeadband(*deadband);
    spaceExplorerSingleFlightController->yaw.addDeadband(*deadband);
    spaceExplorerSingleFlightController->x.addDeadband(*deadband);
    spaceExplorerSingleFlightController->y.addDeadband(*deadband);
    spaceExplorerSingleFlightController->z.addDeadband(*deadband);

    return spaceExplorerSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(const SpaceNavigator& spaceNavigator) {
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

    Deadband *deadband = new Deadband(-0.05, 0.05);
    spaceNavigatorSingleFlightController->roll.addDeadband(*deadband);
    spaceNavigatorSingleFlightController->pitch.addDeadband(*deadband);
    spaceNavigatorSingleFlightController->yaw.addDeadband(*deadband);
    spaceNavigatorSingleFlightController->x.addDeadband(*deadband);
    spaceNavigatorSingleFlightController->y.addDeadband(*deadband);
    spaceNavigatorSingleFlightController->z.addDeadband(*deadband);

    return spaceNavigatorSingleFlightController;
}

SingleFlightController* SingleFlightController::createInstance(const Gravis& gravis) {
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

SingleFlightController* SingleFlightController::createInstance(const DualShock3& dualShock3) {
    CompositeInput* z = new CompositeInput();
    z->addInput(dualShock3.triangleButton);
    z->addInput(dualShock3.xButton, -1);

    CompositeInput* roll = new CompositeInput();
    roll->addInput(dualShock3.leftTrigger, -1);
    roll->addInput(dualShock3.rightTrigger);

    SingleFlightController *dualShock3SingleFlightController =
      new SingleFlightController(
      *roll,
      dualShock3.rightAnalogUpDownPivot,
      dualShock3.rightAnalogLeftRightPivot,
      dualShock3.leftAnalogUpDownPivot,
      dualShock3.leftAnalogLeftRightPivot,
      *z);

    dualShock3SingleFlightController->x.setInverted(true);
    dualShock3SingleFlightController->y.setInverted(true);
    dualShock3SingleFlightController->pitch.setInverted(true);
    dualShock3SingleFlightController->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    dualShock3SingleFlightController->pitch.addDeadband(*deadband);
    dualShock3SingleFlightController->yaw.addDeadband(*deadband);
    dualShock3SingleFlightController->x.addDeadband(*deadband);
    dualShock3SingleFlightController->y.addDeadband(*deadband);

    return dualShock3SingleFlightController;
}

