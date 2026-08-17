#include "idf/WarthogStickBase.hh"

namespace idf
{

WarthogStickBase::WarthogStickBase()
    : forwardBackwardPivot(0, 65535, 32767),
      leftRightPivot(0, 65535, 32767),
      hatNorth(0, 1),
      hatNorthEast(0, 1),
      hatEast(0, 1),
      hatSouthEast(0, 1),
      hatSouth(0, 1),
      hatSouthWest(0, 1),
      hatWest(0, 1),
      hatNorthWest(0, 1),
      trigger(0, 1),
      button2(0, 1),
      button3(0, 1),
      button4(0, 1),
      button5(0, 1),
      button6(0, 1),
      button7(0, 1),
      button8(0, 1),
      button9(0, 1),
      button10(0, 1),
      button11(0, 1),
      button12(0, 1),
      button13(0, 1),
      button14(0, 1),
      button15(0, 1),
      button16(0, 1),
      button17(0, 1),
      button18(0, 1),
      button19(0, 1)
{
}

const std::vector<InputLayout::Configurable> & WarthogStickBase::getConfigurables()
{
    static std::vector<Configurable> inputs;
    if(inputs.empty())
    {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(forwardBackwardPivot, "Forward Backward Pivot", "forwardBackwardPivot"));
        inputs.push_back(Configurable(leftRightPivot, "Left Right Pivot", "leftRightPivot"));
    }

    return inputs;
}

} // namespace idf
