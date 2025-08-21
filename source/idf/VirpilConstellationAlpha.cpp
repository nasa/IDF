#include "idf/VirpilConstellationAlpha.hh"

namespace idf {

VirpilConstellationAlpha::VirpilConstellationAlpha() :
   VirpilMT50CM3( &flipTriggerFwd, &flipTriggerMid, &flipTriggerBack, &trigger,
                  &triggerStage2, &thumbStickIn, &button2, &castleIn,
                  &castleUp, &castleLeft, &castleDown, &castleRight,
                  &button3, &hat1In, &hat1Up, &hat1Left,
                  &hat1Down, &hat1Right, &wheelClick1, &wheelClick2,
                  &wheelUp, &wheelDown, &hat2In, &hat2Up,
                  &hat2Left, &hat2Down, &hat2Right, &hat3In,
                  &hat3Up, &hat3down, &pinkyBtn, &paddleBtn),
   flipTriggerFwd(0, 1),
   flipTriggerMid(0, 1),
   flipTriggerBack(0 ,1),
   trigger(0, 1),
   triggerStage2(0, 1),
   thumbStickIn(0, 1),
   button2(0, 1),
   castleIn(0, 1),
   castleUp(0, 1),
   castleLeft(0, 1),
   castleDown(0, 1),
   castleRight(0, 1),
   button3(0, 1),
   hat1In(0, 1),
   hat1Up(0, 1),
   hat1Left(0, 1),
   hat1Down(0, 1),
   hat1Right(0, 1),
   wheelClick1(0, 1),
   wheelClick2(0, 1),
   wheelUp(0, 1),
   wheelDown(0, 1),
   hat2In(0, 1),
   hat2Up(0, 1),
   hat2Left(0, 1),
   hat2Down(0, 1),
   hat2Right(0, 1),
   hat3In(0, 1),
   hat3Up(0, 1),
   hat3down(0, 1),
   pinkyBtn(0, 1),
   paddleBtn(0, 1) {}

const std::vector<InputLayout::Configurable>& VirpilConstellationAlpha::getConfigurables() {
   static std::vector<Configurable> inputs;
   if (inputs.empty()) {
      append(InputLayout::getConfigurables(), inputs);
      inputs.push_back(Configurable(forwardBackwardPivot, "Forward/Backward Pivot", "forwardBackwardPivot"));
      inputs.push_back(Configurable(leftRightPivot, "Left/Right Pivot", "leftRightPivot"));
      inputs.push_back(Configurable(twist, "Twist", "twist"));
      inputs.push_back(Configurable(forwardBackwardTranslation, "Forward/Backward Translation", "forwardBackwardTranslation"));
      inputs.push_back(Configurable(leftRightTranslation, "Left/Right Translation", "leftRightTranslation"));
      inputs.push_back(Configurable(slider, "Slider", "slider"));
   }
   return inputs;
}


} // namespace
