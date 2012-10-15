#include "Output.hh"

using namespace idf;

Output::Output(Input& in) :
    input(&in),
    minimum(-1),
    maximum(1),
    neutral(0),
    inverted(false) {}

void Output::setInput(Input& in) {
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

bool Output::isInverted() {
    return inverted;
}

double Output::getMinimumValue() {
    return minimum;
}

double Output::getMaximumValue() {
    return maximum;
}

double Output::getNeutralValue() {
    return neutral;
}

double Output::getValue() {
    double normalizedValue = input->getNormalizedValue();
    return neutral + normalizedValue *
      (normalizedValue < 0 ?
        (neutral - (inverted ? maximum : minimum)) :
        ((inverted ? minimum : maximum) - neutral));
}
