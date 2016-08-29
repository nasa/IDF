#include "idf/Deadband.hh"

namespace idf {

Deadband::Deadband(double lower, double upper) {
    setRange(lower, upper);
}

Deadband::Deadband(double lower, double upper, double val) {
    setRange(lower, upper, val);
}

void Deadband::setRange(double lower, double upper) {
    setRange(lower, upper, (lower + upper) / 2);
}

void Deadband::setRange(double lower, double upper, double val) {
    lowerBound = lower;
    upperBound = upper;
    value = val;
}

double Deadband::getLowerBound() const {
    return lowerBound;
}

double Deadband::getUpperBound() const {
    return upperBound;
}

double Deadband::getDeadbandValue() const {
    return value;
}

double Deadband::filter(double val) const {
    return val > lowerBound && val < upperBound ? value : val;
}

bool Deadband::operator ==(const Deadband& other) const {
    return lowerBound == other.lowerBound &&
      upperBound == other.upperBound &&
      value == other.value;
}

}
