#include "Output.hh"

using namespace hardware;

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
    double inputValue = input->getValue();
    double inputNeutral = input->getNeutralValue();

    return inputValue < inputNeutral ?

      neutral + (inputValue - inputNeutral) /
      (input->getMinimumValue() - inputNeutral) *
      ((inverted ? maximum : minimum) - neutral) :

      neutral + (inputValue - inputNeutral) /
      (input->getMaximumValue() - inputNeutral) *
      ((inverted ? minimum : maximum) - neutral);
}
