#include "SingleFlightController.hh"
#include "inputAbstraction/include/CompositeInput.hh"

using namespace hardware;

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

    return new SingleFlightController(wingMan.leftRightPivot,
      wingMan.forwardBackwardPivot, wingMan.twist, *x, *y, *z);
}

SingleFlightController* SingleFlightController::createInstance(SpaceNavigator& spaceNavigator) {
    return new SingleFlightController(
      spaceNavigator.leftRightPivot,
      spaceNavigator.forwardBackwardPivot,
      spaceNavigator.twist,
      spaceNavigator.forwardBackwardTranslation,
      spaceNavigator.leftRightTranslation,
      spaceNavigator.upDownTranslation);
}
