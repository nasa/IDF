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
    y->addInput(wingMan.hatWest, -1);
    y->addInput(wingMan.hatEast);

    CompositeInput* z = new CompositeInput();
    z->addInput(wingMan.button4, -1);
    z->addInput(wingMan.button5);

    return new SingleFlightController(wingMan.leftRightPivot,
      wingMan.forwardBackwardPivot, wingMan.twist, *x, *y, *z);
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
    spaceNavigatorSingleFlightController->roll.setInverted(true);

    return spaceNavigatorSingleFlightController;
}
