#include "CompositeInput.hh"
#include <algorithm>
#include <cmath>

using namespace idf;

CompositeInput::CompositeInput(bool simple) :
    simpleCombination(simple) {}

double CompositeInput::getMinimumValue() {
    return -getMaximumValue();
}

double CompositeInput::getNeutralValue() {
    return 0;
}

double CompositeInput::getMaximumValue() {
    double maximum = 0;

    if (simpleCombination) {
        for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
            maximum = std::max(maximum, fabs((*i)->weight));
        }
    }
    else {
        for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
            maximum += fabs((*i)->weight);
        }
    }

    return maximum;
}

double CompositeInput::getValue() {
    double result = 0;

    for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        result += (*i)->weight * (*i)->input->getNormalizedValue();
    }

    return result < getMinimumValue() ? getMinimumValue() :
       result > getMaximumValue() ? getMaximumValue() : result;
}

void CompositeInput::addInput(Input& input, double weight) {
    // Add the input, if not present.
    for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        if ((*i)->input == &input) {
            return;
        }
    }
    components.push_back(new Component(input, weight));
}

void CompositeInput::removeInput(Input& input) {
    // Remove the input, if present.
    for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        if ((*i)->input == &input) {
            components.erase(i);
            break;
        }
    }
}

CompositeInput::Component::Component(Input& in, double wght) :
    input(&in),
    weight(wght) {}
