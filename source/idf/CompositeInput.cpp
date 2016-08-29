#include "idf/CompositeInput.hh"
#include <algorithm>
#include <cmath>

namespace idf {

CompositeInput::CompositeInput(bool simple) :
    simpleCombination(simple) {}

double CompositeInput::getMinimumValue() const {
    return -getMaximumValue();
}

double CompositeInput::getNeutralValue() const {
    return 0;
}

double CompositeInput::getMaximumValue() const {
    double maximum = 0;

    if (simpleCombination) {
        for (std::vector<const Component*>::const_iterator i = components.begin(); i != components.end(); ++i) {
            maximum = std::max(maximum, fabs((*i)->weight));
        }
    }
    else {
        for (std::vector<const Component*>::const_iterator i = components.begin(); i != components.end(); ++i) {
            maximum += fabs((*i)->weight);
        }
    }

    return maximum;
}

double CompositeInput::getValue() const {
    double result = 0;

    for (std::vector<const Component*>::const_iterator i = components.begin(); i != components.end(); ++i) {
        result += (*i)->weight * (*i)->input->getNormalizedValue();
    }

    return result < getMinimumValue() ? getMinimumValue() :
       result > getMaximumValue() ? getMaximumValue() : result;
}

void CompositeInput::addInput(const Input& input, double weight) {
    // Add the input, if not present.
    for (std::vector<const Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        if ((*i)->input == &input) {
            return;
        }
    }
    components.push_back(new Component(input, weight));
}

void CompositeInput::removeInput(const Input& input) {
    // Remove the input, if present.
    for (std::vector<const Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        if ((*i)->input == &input) {
            components.erase(i);
            break;
        }
    }
}

CompositeInput::Component::Component(const Input& in, double wght) :
    input(&in),
    weight(wght) {}

}
