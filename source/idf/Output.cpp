#include "idf/Output.hh"

#include <algorithm>

namespace idf {

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

    value = applyDeadbands(value);

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

    value = (value - neutral) /
      (value < neutral ? (neutral - minimum) : (maximum - neutral));

      return applyNormalizedDeadbands(value);
}

}
