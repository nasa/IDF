#include "idf/Input.hh"

namespace idf {

double Input::getNormalizedValue() const {
    double value = getValue();
    double neutral = getNeutralValue();

    return (value - neutral) /
      (value < neutral ? (neutral - getMinimumValue()) : (getMaximumValue() - neutral));
}

}
