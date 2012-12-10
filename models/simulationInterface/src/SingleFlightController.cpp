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

    SingleFlightController *controller =
      new SingleFlightController(wingMan.leftRightPivot,
      wingMan.forwardBackwardPivot, wingMan.twist, *x, *y, *z);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    controller->roll.addDeadband(*deadband);
    controller->pitch.addDeadband(*deadband);
    controller->yaw.addDeadband(*deadband);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const SpaceExplorer& spaceExplorer) {
    SingleFlightController *controller =
      new SingleFlightController(
      spaceExplorer.leftRightPivot,
      spaceExplorer.forwardBackwardPivot,
      spaceExplorer.twist,
      spaceExplorer.forwardBackwardTranslation,
      spaceExplorer.leftRightTranslation,
      spaceExplorer.upDownTranslation);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->z.setInverted(true);
    controller->roll.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    controller->roll.addDeadband(*deadband);
    controller->pitch.addDeadband(*deadband);
    controller->yaw.addDeadband(*deadband);
    controller->x.addDeadband(*deadband);
    controller->y.addDeadband(*deadband);
    controller->z.addDeadband(*deadband);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const SpaceNavigator& spaceNavigator) {
    SingleFlightController *controller =
      new SingleFlightController(
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardTranslation,
      spaceNavigator.leftRightTranslation,
      spaceNavigator.upDownTranslation);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->z.setInverted(true);
    controller->roll.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    controller->roll.addDeadband(*deadband);
    controller->pitch.addDeadband(*deadband);
    controller->yaw.addDeadband(*deadband);
    controller->x.addDeadband(*deadband);
    controller->y.addDeadband(*deadband);
    controller->z.addDeadband(*deadband);

    return controller;
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

    SingleFlightController *controller =
      new SingleFlightController(
      *roll,
      dualShock3.rightAnalogUpDownPivot,
      dualShock3.rightAnalogLeftRightPivot,
      dualShock3.leftAnalogUpDownPivot,
      dualShock3.leftAnalogLeftRightPivot,
      *z);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    controller->pitch.addDeadband(*deadband);
    controller->yaw.addDeadband(*deadband);
    controller->x.addDeadband(*deadband);
    controller->y.addDeadband(*deadband);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const VirtualLayout& virtualLayout) {
    return new SingleFlightController(
      virtualLayout.clockwiseCounterclockwiseRotation,
      virtualLayout.upDownRotation,
      virtualLayout.leftRightRotation,
      virtualLayout.inOutTranslation,
      virtualLayout.leftRightTranslation,
      virtualLayout.upDownTranslation);
}

SingleFlightController* SingleFlightController::createInstance(const ThrustMaster& thrustMaster) {
    SingleFlightController *controller =
      new SingleFlightController(
      thrustMaster.leftRightPivot,
      thrustMaster.forwardBackwardPivot,
      thrustMaster.twist,
      thrustMaster.forwardBackwardTranslation,
      thrustMaster.leftRightTranslation,
      thrustMaster.upDownTranslation);

    controller->y.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    Deadband *deadband = new Deadband(-0.05, 0.05);
    controller->roll.addDeadband(*deadband);
    controller->pitch.addDeadband(*deadband);
    controller->yaw.addDeadband(*deadband);
    controller->x.addDeadband(*deadband);
    controller->y.addDeadband(*deadband);
    controller->z.addDeadband(*deadband);

    return controller;
}
