#include "SingleRoboticsController.hh"

using namespace idf;

SingleRoboticsController::SingleRoboticsController(
  const Input& rollInput, const Input& pitchInput, const Input& yawInput,
  const Input& xInput, const Input& yInput, const Input& zInput,
  const Input& triggerInput, const Input& rateModeInput) :
    roll(rollInput), pitch(pitchInput), yaw(yawInput),
    x(xInput), y(yInput), z(zInput),
    trigger(triggerInput), rateMode(rateModeInput) {}

void SingleRoboticsController::addDeadband(const Deadband& deadband) {
    roll.addDeadband(deadband);
    pitch.addDeadband(deadband);
    yaw.addDeadband(deadband);
    x.addDeadband(deadband);
    y.addDeadband(deadband);
    z.addDeadband(deadband);
}

void SingleRoboticsController::clearDeadbands() {
    roll.clearDeadbands();
    pitch.clearDeadbands();
    yaw.clearDeadbands();
    x.clearDeadbands();
    y.clearDeadbands();
    z.clearDeadbands();
}

double SingleRoboticsController::getCommandedRoll() const {
    return roll.getNormalizedValue();
}

double SingleRoboticsController::getCommandedPitch() const {
    return pitch.getNormalizedValue();
}

double SingleRoboticsController::getCommandedYaw() const {
    return yaw.getNormalizedValue();
}

double SingleRoboticsController::getCommandedX() const {
    return x.getNormalizedValue();
}

double SingleRoboticsController::getCommandedY() const {
    return y.getNormalizedValue();
}

double SingleRoboticsController::getCommandedZ() const {
    return z.getNormalizedValue();
}

bool SingleRoboticsController::getCommandedTrigger() const {
    return trigger.getNormalizedValue() > 0;
}

bool SingleRoboticsController::getCommandedRateMode() const {
    return rateMode.getNormalizedValue() > 0;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const WingMan& wingMan) {
    CompositeInput* x = new CompositeInput();
    x->addInput(wingMan.hatNorth);
    x->addInput(wingMan.hatSouth, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(wingMan.hatWest);
    y->addInput(wingMan.hatEast, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(wingMan.button4);
    z->addInput(wingMan.button5, -1);

    SingleRoboticsController *controller =
      new SingleRoboticsController(wingMan.leftRightPivot,
      wingMan.forwardBackwardPivot, wingMan.twist, *x, *y, *z,
      wingMan.trigger, wingMan.slider);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const SpaceExplorer& spaceExplorer) {
    SingleRoboticsController *controller =
      new SingleRoboticsController(
      spaceExplorer.leftRightPivot,
      spaceExplorer.forwardBackwardPivot,
      spaceExplorer.twist,
      spaceExplorer.forwardBackwardTranslation,
      spaceExplorer.leftRightTranslation,
      spaceExplorer.upDownTranslation,
      spaceExplorer.buttonShift,
      spaceExplorer.buttonAlt);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->z.setInverted(true);
    controller->roll.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const SpaceNavigator& spaceNavigator) {
    SingleRoboticsController *controller =
      new SingleRoboticsController(
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardTranslation,
      spaceNavigator.leftRightTranslation,
      spaceNavigator.upDownTranslation,
      spaceNavigator.leftButton,
      spaceNavigator.rightButton);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->z.setInverted(true);
    controller->roll.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const Gravis& gravis) {
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

    return new SingleRoboticsController(*roll, *pitch, *yaw, *x, *y, *z,
      gravis.startButton, gravis.selectButton);
}

SingleRoboticsController* SingleRoboticsController::createInstance(const DualShock3& dualShock3) {
    CompositeInput* z = new CompositeInput();
    z->addInput(dualShock3.triangleButton);
    z->addInput(dualShock3.xButton, -1);

    CompositeInput* roll = new CompositeInput();
    roll->addInput(dualShock3.leftTrigger, -1);
    roll->addInput(dualShock3.rightTrigger);

    SingleRoboticsController *controller =
      new SingleRoboticsController(
      *roll,
      dualShock3.rightAnalogUpDownPivot,
      dualShock3.rightAnalogLeftRightPivot,
      dualShock3.leftAnalogUpDownPivot,
      dualShock3.leftAnalogLeftRightPivot,
      *z,
      dualShock3.startButton,
      dualShock3.selectButton);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const VirtualLayout& virtualLayout) {
    SingleInput* dummyInput = new SingleInput(-1, 1);

    return new SingleRoboticsController(
      virtualLayout.clockwiseCounterclockwiseRotation,
      virtualLayout.upDownRotation,
      virtualLayout.leftRightRotation,
      virtualLayout.inOutTranslation,
      virtualLayout.leftRightTranslation,
      virtualLayout.upDownTranslation,
      *dummyInput, *dummyInput);
}

SingleRoboticsController* SingleRoboticsController::createInstance(const ThrustMaster& thrustMaster) {
    SingleInput* dummyInput = new SingleInput(-1, 1);

    SingleRoboticsController *controller =
      new SingleRoboticsController(
      thrustMaster.leftRightPivot,
      thrustMaster.forwardBackwardPivot,
      thrustMaster.twist,
      thrustMaster.forwardBackwardTranslation,
      thrustMaster.leftRightTranslation,
      thrustMaster.upDownTranslation,
      *dummyInput, *dummyInput);

    controller->y.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    if (thrustMaster.male) {
        controller->z.setInverted(true);
    }

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const IndustrialProducts& industrialProducts) {
    CompositeInput* z = new CompositeInput();
    z->addInput(industrialProducts.switchUp);
    z->addInput(industrialProducts.switchDown, -1);

    SingleRoboticsController *controller =
      new SingleRoboticsController(
      industrialProducts.leftRightPivot,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.twist,
      industrialProducts.hatUpDownPivot,
      industrialProducts.hatLeftRightPivot,
      *z,
      industrialProducts.trigger,
      industrialProducts.switchUp);

    controller->yaw.setInverted(true);
    controller->y.setInverted(true);

    return controller;
}

SingleRoboticsController* SingleRoboticsController::createInstance(const IndustrialProducts2& industrialProducts2) {
    CompositeInput* x = new CompositeInput();
    x->addInput(industrialProducts2.hatNorth);
    x->addInput(industrialProducts2.hatSouth, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(industrialProducts2.hatWest);
    y->addInput(industrialProducts2.hatEast, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(industrialProducts2.northEastButton);
    z->addInput(industrialProducts2.southEastButton, -1);

    SingleRoboticsController *controller =
      new SingleRoboticsController(
      industrialProducts2.leftRightPivot,
      industrialProducts2.forwardBackwardPivot,
      industrialProducts2.twist,
      *x, *y, *z,
      industrialProducts2.trigger,
      industrialProducts2.southWestButton);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}
