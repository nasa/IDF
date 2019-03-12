#include "idf/Deadbandable.hh"

#include <algorithm>

namespace idf {

void Deadbandable::addDeadband(const Deadband& deadband, std::vector<Deadband>& filters) {
    // Add the deadband, if not present.
    if (std::find(filters.begin(), filters.end(), deadband) == filters.end()) {
        filters.push_back(deadband);
    }
}

void Deadbandable::addDeadband(const Deadband& deadband) {
    addDeadband(deadband, deadbands);
}

void Deadbandable::addNormalizedDeadband(const Deadband& deadband) {
    addDeadband(deadband, normalizedDeadbands);
}

void Deadbandable::removeDeadband(const Deadband& deadband) {
    // Remove the deadband, if present.
    deadbands.erase(std::remove(deadbands.begin(), deadbands.end(), deadband), deadbands.end());
    normalizedDeadbands.erase(std::remove(normalizedDeadbands.begin(), normalizedDeadbands.end(), deadband), normalizedDeadbands.end());
}

void Deadbandable::clearDeadbands() {
    deadbands.clear();
    normalizedDeadbands.clear();
}

const std::vector<Deadband>& Deadbandable::getDeadbands() const {
    return deadbands;
}

const std::vector<Deadband>& Deadbandable::getNormalizedDeadbands() const {
    return normalizedDeadbands;
}

double Deadbandable::applyDeadbands(double value, const std::vector<Deadband>& filters) const {
    for (std::vector<Deadband>::const_iterator i = filters.begin(); i != filters.end(); ++i) {
        value = i->filter(value);
    }
    return value;
}

double Deadbandable::applyDeadbands(double value) const {
    return applyDeadbands(value, deadbands);
}

double Deadbandable::applyNormalizedDeadbands(double value) const {
    return applyDeadbands(value, normalizedDeadbands);
}

}
