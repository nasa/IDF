#include "Output.hh"

#include <algorithm>

using namespace idf;

Output::Output(const Input& in) :
    input(&in),
    inverted(false),
    toggle(false),
    toggleValue(-1),
    lastValue(0) {
    setRange(-1, 1);
}

void Output::setInput(const Input& in) {
    input = &in;
}

void Output::setRange(double min, double max) {
    setRange(min, max, (min + max) / 2);
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

void Output::setToggle(bool tog) {
    toggle = tog;
}

bool Output::isToggle() const {
    return toggle;
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

    for (std::vector<Deadband>::const_iterator i = deadbands.begin(); i != deadbands.end(); ++i) {
        value = i->filter(value);
    }

    if (lastValue <= neutral && value > neutral) {
        toggleValue = toggleValue == minimum ? maximum : minimum;
    }
    lastValue = value;

    return toggle ? toggleValue : value;
}

double Output::getNormalizedValue() const {
    double value = getValue();

    // This check is necessary to prevent a division by zero when
    // value == neutral == maximum
    if (value == maximum) {
        return 1;
    }

    return (value - neutral) /
      (value < neutral ? (neutral - minimum) : (maximum - neutral));
}

void Output::addDeadband(const Deadband& deadband) {
    // Add the deadband, if not present.
    if(std::find(deadbands.begin(), deadbands.end(), deadband) == deadbands.end()) {
        deadbands.push_back(deadband);
    }
}

void Output::removeDeadband(const Deadband& deadband) {
    // Remove the deadband, if present.
    deadbands.erase(std::remove(deadbands.begin(), deadbands.end(), deadband), deadbands.end());
}

void Output::clearDeadbands() {
    deadbands.clear();
}

const std::vector<Deadband>& Output::getDeadbands() const {
    return deadbands;
}
