#include "SingleInput.hh"
#include <cmath>

using namespace idf;

SingleInput::SingleInput(double min, double max) {
    initialize(min, max, (min + max) / 2);
}

SingleInput::SingleInput(double min, double max, double middle) {
    initialize(min, max, middle);
}

double SingleInput::getMinimumValue() {
    return minimum;
}

double SingleInput::getNeutralValue() {
    return neutral;
}

double SingleInput::getMaximumValue() {
    return maximum;
}

double SingleInput::getValue() {
    return value;
}

void SingleInput::setValue(double rawValue) {
    value = rawValue;
}

void SingleInput::initialize(double min, double  max, double middle) {
    minimum = min;
    maximum = max;
    neutral = middle;
    value = neutral;
}
