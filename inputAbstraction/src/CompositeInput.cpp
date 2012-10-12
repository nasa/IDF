#include "CompositeInput.hh"
#include <algorithm>
#include <cmath>

using namespace hardware;

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
    components.push_back(new Component(input, weight));
}

void CompositeInput::removeInput(Input& input) {
    for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); ++i) {
        if ((*i)->input == &input) {
            components.erase(i);
            break;
        }
    }
}

#include "SingleInput.hh"
void CompositeInput::unitTest() {
    SingleInput input1(-1, 1);
    SingleInput input2(-1, 1);

    CompositeInput compositeInput(true);
    compositeInput.addInput(input1);
    compositeInput.addInput(input2, 2);

    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input1.setValue(input1.getMaximumValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input2.setValue(input2.getMaximumValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input1.setValue(input1.getNeutralValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input1.setValue(input1.getMinimumValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input2.setValue(input2.getNeutralValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;

    input2.setValue(input2.getMinimumValue());
    std::cout << input1.getValue() << " "
              << input2.getValue() << " => "
              << compositeInput.getNormalizedValue() << std::endl;
}


CompositeInput::Component::Component(Input& in, double wght) :
    input(&in),
    weight(wght) {}
