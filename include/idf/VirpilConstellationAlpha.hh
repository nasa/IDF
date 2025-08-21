/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/VirpilConstellationAlpha.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/VirpilConstellationAlpha.cpp}
 */

#ifndef VIRPIL_CONSTELLATION_ALPHA_HH
#define VIRPIL_CONSTELLATION_ALPHA_HH

#include "idf/InputLayout.hh"
#include "idf/VirpilMT50CM3.hh"

namespace idf {

/**
 * %Virtual Pilot's Constellation Alpha hand controller input layout
 *
 * @author Philip Kunz
 */
class VirpilConstellationAlpha : public VirpilMT50CM3, public virtual InputLayout {

   public:

   // constructor
   VirpilConstellationAlpha();

   // destructor
   virtual ~VirpilConstellationAlpha() {};

   // Flip Trigger - forward position
   SingleInput flipTriggerFwd;

   // Flip Trigger - middle position
   SingleInput flipTriggerMid;

   // Flip Trigger - pulled back position
   SingleInput flipTriggerBack;

   // Standard Trigger
   SingleInput trigger;

   // Standard Trigger - 2nd stage
   SingleInput triggerStage2;

   // Analog Stick - Click In
   SingleInput thumbStickIn;

   // Momentary button right of the analog stick
   SingleInput button2;

   // Hat to the upper left - click in
   SingleInput castleIn;

   // Hat to the upper left - up
   SingleInput castleUp;

   // Hat to the upper left - left
   SingleInput castleLeft;

   // Hat to the upper left - down
   SingleInput castleDown;

   // Hat to the upper left - right
   SingleInput castleRight;

   // Button below the Castle
   SingleInput button3;

   // Hat in middle of Joystick - click in
   SingleInput hat1In;

   // Hat in middle of Joystick - up
   SingleInput hat1Up;

   // Hat in middle of Joystick - left
   SingleInput hat1Left;

   // Hat in middle of Joystick - down
   SingleInput hat1Down;

   // Hat in middle of Joystick - right
   SingleInput hat1Right;

   // Wheel - click in stage 1
   SingleInput wheelClick1;

   // Wheel - click in stage 2
   SingleInput wheelClick2;

   // Wheel - up
   SingleInput wheelUp;

   // Wheel - down
   SingleInput wheelDown;

   // Hat (Thumb Rest) - click in
   SingleInput hat2In;

   // Hat (Thumb Rest) - up
   SingleInput hat2Up;

   // Hat (Thumb Rest) - left
   SingleInput hat2Left;

   // Hat (Thumb Rest) - down
   SingleInput hat2Down;

   // Hat (Thumb Rest) - right
   SingleInput hat2Right;

   // Hat (Index Finger) - click in
   SingleInput hat3In;

   // Hat (Index Finger) - up
   SingleInput hat3Up;

   // Hat (Index Finger) - down
   SingleInput hat3down;

   // Pinky button
   SingleInput pinkyBtn;

   // Paddle Momentary Button
   SingleInput paddleBtn;

   protected:

   virtual const std::vector<Configurable>& getConfigurables();

};

} // namespace

#endif
