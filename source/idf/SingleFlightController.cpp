#include "idf/SingleFlightController.hh"

namespace idf {

SingleFlightController::SingleFlightController(
  const Input& rollInput, const Input& pitchInput, const Input& yawInput,
  const Input& xInput, const Input& yInput, const Input& zInput) :
    roll(rollInput), pitch(pitchInput), yaw(yawInput),
    x(xInput), y(yInput), z(zInput) {}

void SingleFlightController::addDeadband(const Deadband& deadband) {
    roll.addDeadband(deadband);
    pitch.addDeadband(deadband);
    yaw.addDeadband(deadband);
    x.addDeadband(deadband);
    y.addDeadband(deadband);
    z.addDeadband(deadband);
}

void SingleFlightController::clearDeadbands() {
    roll.clearDeadbands();
    pitch.clearDeadbands();
    yaw.clearDeadbands();
    x.clearDeadbands();
    y.clearDeadbands();
    z.clearDeadbands();
}

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

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const Extreme3dPro& extreme3dPro) {
    CompositeInput* x = new CompositeInput();
    x->addInput(extreme3dPro.hatNorth);
    x->addInput(extreme3dPro.hatSouth, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(extreme3dPro.hatWest);
    y->addInput(extreme3dPro.hatEast, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(extreme3dPro.button6);
    z->addInput(extreme3dPro.button4, -1);

    SingleFlightController *controller =
      new SingleFlightController(extreme3dPro.leftRightPivot,
      extreme3dPro.forwardBackwardPivot, extreme3dPro.twist, *x, *y, *z);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const SpaceBase& spaceBase) {
    SingleFlightController *controller =
      new SingleFlightController(
      spaceBase.leftRightPivot,
      spaceBase.forwardBackwardPivot,
      spaceBase.twist,
      spaceBase.forwardBackwardTranslation,
      spaceBase.leftRightTranslation,
      spaceBase.upDownTranslation);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->z.setInverted(true);
    controller->roll.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

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

SingleFlightController* SingleFlightController::createInstance(const DualShock& dualShock) {
    CompositeInput* z = new CompositeInput();
    z->addInput(dualShock.triangleButton);
    z->addInput(dualShock.xButton, -1);

    CompositeInput* roll = new CompositeInput();
    roll->addInput(dualShock.leftTrigger, -1);
    roll->addInput(dualShock.rightTrigger);

    SingleFlightController *controller =
      new SingleFlightController(
      *roll,
      dualShock.rightAnalogUpDownPivot,
      dualShock.rightAnalogLeftRightPivot,
      dualShock.leftAnalogUpDownPivot,
      dualShock.leftAnalogLeftRightPivot,
      *z);

    controller->x.setInverted(true);
    controller->y.setInverted(true);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

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

SingleFlightController* SingleFlightController::createInstance(const ThrustMasterBase& thrustMaster) {
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

    if (thrustMaster.male) {
        controller->z.setInverted(true);
    }

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const IndustrialProducts& industrialProducts) {
    CompositeInput* z = new CompositeInput();
    z->addInput(industrialProducts.switchUp);
    z->addInput(industrialProducts.switchDown, -1);

    SingleFlightController *controller =
      new SingleFlightController(
      industrialProducts.leftRightPivot,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.twist,
      industrialProducts.hatUpDownPivot,
      industrialProducts.hatLeftRightPivot,
      *z);

    controller->yaw.setInverted(true);
    controller->y.setInverted(true);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const IndustrialProducts2& industrialProducts2) {
    CompositeInput* x = new CompositeInput();
    x->addInput(industrialProducts2.hatNorth);
    x->addInput(industrialProducts2.hatSouth, -1);

    CompositeInput* y = new CompositeInput();
    y->addInput(industrialProducts2.hatWest);
    y->addInput(industrialProducts2.hatEast, -1);

    CompositeInput* z = new CompositeInput();
    z->addInput(industrialProducts2.northEastButton);
    z->addInput(industrialProducts2.southEastButton, -1);

    SingleFlightController *controller =
      new SingleFlightController(
      industrialProducts2.leftRightPivot,
      industrialProducts2.forwardBackwardPivot,
      industrialProducts2.twist,
      *x, *y, *z);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const IndustrialProducts3& industrialProducts) {
    CompositeInput* z = new CompositeInput();
    z->addInput(industrialProducts.switchUp);
    z->addInput(industrialProducts.switchDown, -1);

    SingleFlightController *controller =
      new SingleFlightController(
      industrialProducts.leftRightPivot,
      industrialProducts.forwardBackwardPivot,
      industrialProducts.twist,
      industrialProducts.hatUpDownPivot,
      industrialProducts.hatLeftRightPivot,
      *z);

    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);
    controller->y.setInverted(true);

    return controller;
}


SingleFlightController* SingleFlightController::createInstance(const SaitekX52& saitekX52) {
    CompositeInput* z = new CompositeInput();
    z->addInput(saitekX52.buttonA, 1);
    z->addInput(saitekX52.buttonB, -1);

    SingleFlightController *controller =
      new SingleFlightController(
        saitekX52.leftRightPivot,
        saitekX52.forwardBackwardPivot,
        saitekX52.twist,
        saitekX52.hat2UpDownPivot,
        saitekX52.hat2LeftRightPivot,
        *z);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

SingleFlightController* SingleFlightController::createInstance(const SaitekX56Stick& saitekX56Stick) {
    SingleFlightController *controller =
      new SingleFlightController(
        saitekX56Stick.leftRightPivot,
        saitekX56Stick.forwardBackwardPivot,
        saitekX56Stick.twist,
        saitekX56Stick.hat2UpDownPivot,
        saitekX56Stick.hat2LeftRightPivot,
        saitekX56Stick.hat1UpDownPivot);
    controller->pitch.setInverted(true);
    controller->yaw.setInverted(true);

    return controller;
}

}
