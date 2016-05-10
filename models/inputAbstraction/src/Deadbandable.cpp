#include "inputAbstraction/include/Deadbandable.hh"

#include <algorithm>

namespace idf {

void Deadbandable::addDeadband(const Deadband& deadband) {
    // Add the deadband, if not present.
    if (std::find(deadbands.begin(), deadbands.end(), deadband) == deadbands.end()) {
        deadbands.push_back(deadband);
    }
}

void Deadbandable::removeDeadband(const Deadband& deadband) {
    // Remove the deadband, if present.
    deadbands.erase(std::remove(deadbands.begin(), deadbands.end(), deadband), deadbands.end());
}

void Deadbandable::clearDeadbands() {
    deadbands.clear();
}

const std::vector<Deadband>& Deadbandable::getDeadbands() const {
    return deadbands;
}

double Deadbandable::applyDeadbands(double value) const {
    for (std::vector<Deadband>::const_iterator i = deadbands.begin(); i != deadbands.end(); ++i) {
        value = i->filter(value);
    }
    return value;
}

}
