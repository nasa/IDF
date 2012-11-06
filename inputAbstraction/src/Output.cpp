#include "Output.hh"

#include <algorithm>

using namespace idf;

Output::Output(const Input& in) :
    input(&in),
    minimum(-1),
    maximum(1),
    neutral(0),
    inverted(false) {}

void Output::setInput(const Input& in) {
    input = &in;
}

void Output::setRange(double min, double max) {
    minimum = min;
    maximum = max;
    neutral = (minimum + maximum) / 2;
}

void Output::setRange(double min, double max, double middle) {
    minimum = min;
    maximum = max;
    neutral = middle;
}

void Output::setInverted(bool flip) {
    inverted = flip;
}

bool Output::isInverted() const {
    return inverted;
}

double Output::getMinimumValue() const {
    return minimum;
}

double Output::getMaximumValue() const {
    return maximum;
}

double Output::getNeutralValue() const {
    return neutral;
}

double Output::getValue() const {
    double normalizedValue = input->getNormalizedValue();

    double value = neutral + normalizedValue *
      (normalizedValue < 0 ?
        (neutral - (inverted ? maximum : minimum)) :
        ((inverted ? minimum : maximum) - neutral));

    for (std::vector<const Deadband*>::const_iterator i = deadbands.begin(); i != deadbands.end(); ++i) {
        value = (*i)->filter(value);
    }

    return value;
}

double Output::getNormalizedValue() const {
    double value = getValue();

    return (value - neutral) /
      (value < neutral ? (neutral - minimum) : (maximum - neutral));
}

void Output::addDeadband(const Deadband& deadband) {
    // Add the deadband, if not present.
    if(std::find(deadbands.begin(), deadbands.end(), &deadband) == deadbands.end()) {
        deadbands.push_back(&deadband);
    }
}

void Output::removeDeadband(const Deadband& deadband) {
    // Remove the deadband, if present.
    deadbands.erase(std::remove(deadbands.begin(), deadbands.end(), &deadband), deadbands.end());
}

const std::vector<const Deadband*>& Output::getDeadbands() const {
    return deadbands;
}
