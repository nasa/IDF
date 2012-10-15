#include "Input.hh"
#include <sstream>
#include <iomanip>

using namespace idf;

std::string Input::toString() {
    std::ostringstream oss;
    oss << std::showpos << std::fixed << std::setprecision(2) << getValue();
    return oss.str();
}

double Input::getNormalizedValue() {
    double value = getValue();
    double neutral = getNeutralValue();

    return (value - neutral) / (value < neutral ?
      (neutral - getMinimumValue()) :
      (getMaximumValue() - neutral));
}
