#include "MutualExclusivityGroup.hh"

#include <algorithm>

using namespace idf;

void MutualExclusivityGroup::add(Controller& controller) {
    // Add the controller, if no present, and begin listening for state changes.
    if (std::find(controllers.begin(), controllers.end(), &controller) == controllers.end()) {
        controllers.push_back(&controller);
        controller.addStateChangeListener(*this);

        // If the controller is active, disable all other controllers.
        if (controller.isActive()) {
            disableOtherControllers(controller);
        }
    }
}

void MutualExclusivityGroup::remove(Controller& controller) {
    std::vector<Controller*>::iterator i =
      std::find(controllers.begin(), controllers.end(), &controller);

    // Remove the controller, if present, and stop listening for state changes.
    if (i != controllers.end()) {
        (*i)->removeStateChangeListener(*this);
        controllers.erase(i, i);
    }
}

void MutualExclusivityGroup::stateChanged(Controller& controller) {
    // If a controller being managed by this instance becomes active,
    // disable all other controllers.
    if (controller.isActive() && std::find(controllers.begin(),
      controllers.end(), &controller) != controllers.end()) {
        disableOtherControllers(controller);
    }
}

void MutualExclusivityGroup::disableOtherControllers(Controller& activeController) {
    for (std::vector<Controller*>::iterator i = controllers.begin(); i != controllers.end(); ++i) {
        if (*i != &activeController) {
            (*i)->setActive(false);
        }
    }
}
