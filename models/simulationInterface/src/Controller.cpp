#include "Controller.hh"

#include <algorithm>

using namespace idf;

Controller::Controller() :
    active(true) {}

Controller::~Controller() {}

void Controller::setActive(bool activate) {
    if (active != activate) {
        active = activate;

        // Notify listeners of state change.
        for (std::vector<StateChangeListener*>::iterator i =
          stateChangeListeners.begin(); i != stateChangeListeners.end(); ++i) {
            (*i)->stateChanged(*this);
        }
    }
}

bool Controller::isActive() const {
    return active;
}

void Controller::addStateChangeListener(StateChangeListener& stateChangeListener) {
    // Add the listener, if not present.
    if (std::find(stateChangeListeners.begin(), stateChangeListeners.end(),
      &stateChangeListener) == stateChangeListeners.end()) {
        stateChangeListeners.push_back(&stateChangeListener);
    }
}

void Controller::removeStateChangeListener(const StateChangeListener& stateChangeListener) {
    // Remove the listener, if present.
    stateChangeListeners.erase(std::remove(stateChangeListeners.begin(),
      stateChangeListeners.end(), &stateChangeListener), stateChangeListeners.end());
}
