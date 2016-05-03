#include "inputAbstraction/include/InputLayout.hh"

namespace idf {

const std::vector<InputLayout::Configurable>& InputLayout::getConfigurables() {
    static std::vector<Configurable> inputs;
    return inputs;
}

InputLayout::Configurable::Configurable(SingleInput& singleInput, const std::string& id, const std::string& variableId) :
    input(&singleInput),
    name(id),
    variable(variableId) {}

}
