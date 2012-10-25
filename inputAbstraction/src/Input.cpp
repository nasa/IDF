#include "Input.hh"

using namespace idf;

double Input::getNormalizedValue() {
    double value = getValue();
    double neutral = getNeutralValue();

    return (value - neutral) /
      (value < neutral ?
        (neutral - getMinimumValue()) :
        (getMaximumValue() - neutral));
}
