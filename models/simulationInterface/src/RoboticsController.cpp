#include "simulationInterface/include/RoboticsController.hh"

namespace idf {

const RoboticsController::Feature<bool> RoboticsController::RATE_MODE([](const RoboticsController& controller) {
    return controller.inactiveRateMode;
});

}
