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
      button2WeaponRelease(0, 1),
      button3NoseSteering(0, 1),
      button4Paddle(0, 1),
      button5MasterMode(0, 1),
      button6Trigger2nd(0, 1),
      button7TmsUp(0, 1),
      button8TmsRight(0, 1),
      button9TmsDown(0, 1),
      button10TmsLeft(0, 1),
      button11DmsUp(0, 1),
      button12DmsRight(0, 1),
      button13DmsDown(0, 1),
      button14DmsLeft(0, 1),
      button15CmsForward(0, 1),
      button16CmsRight(0, 1),
      button17CmsBack(0, 1),
      button18CmsLeft(0, 1),
      button19CmsPush(0, 1)
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
