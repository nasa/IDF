#include "idf/SingleInput.hh"
#include <stdexcept>
#include <sstream>

namespace idf {

SingleInput::SingleInput(double min, double max) {
    configure(min, max);
}

SingleInput::SingleInput(double min, double max, double middle) {
    configure(min, max, middle);
}

void SingleInput::configure(double min, double  max) {
    configure(min, max, (min + max) / 2);
}

void SingleInput::configure(double min, double max, double middle) {
    if (min > max) {
        std::ostringstream stream;
        stream << " Minimum (" << min << ") must not be greater than maximum (" << max << ").";
        throw std::logic_error(stream.str());
    }

    if (middle < min) {
        std::ostringstream stream;
        stream << " Neutral (" << middle << ") must not be less than minimum (" << min << ").";
        throw std::logic_error(stream.str());
    }

    if (middle > max) {
        std::ostringstream stream;
        stream << " Neutral (" << middle << ") must not be greater than maximum (" << max << ").";
        throw std::logic_error(stream.str());
    }

    minimum = min;
    maximum = max;
    neutral = middle;
    value = neutral;
}

double SingleInput::getMinimumValue() const {
    return minimum;
}

double SingleInput::getNeutralValue() const {
    return neutral;
}

double SingleInput::getMaximumValue() const {
    return maximum;
}

double SingleInput::getValue() const {
    return applyDeadbands(value);
}

void SingleInput::setValue(double rawValue) {
    value = rawValue;
}

}
