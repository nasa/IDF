/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/VirpilMT50CM3.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/VirpilMT50CM3.cpp}
 */

#ifndef VIRPIL_MT_50CM3_BASE_HH
#define VIRPIL_MT_50CM3_BASE_HH

#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Virtual Pilot Controls' R-VPC MT-50CM3 Joystick Base implementation. This device serves
 * as a base for a number of compatible grips. Thus, this base class needs to be a little
 * different and more flexible. Since this device is what actually connects to the host,
 * it makes some sense that this class should have the decode logic, even though it is 
 * not derived from UsbDevice.
 *
 * While many of the comaptible grips have multiple Hat switches, this base presents them as
 * just a collection of buttons
 *
 * @author Philip Kunz
 */
class VirpilMT50CM3 {

   public:

   // constructor
   VirpilMT50CM3(SingleInput* b1, SingleInput* b2, SingleInput* b3, SingleInput* b4,
                 SingleInput* b5, SingleInput* b6, SingleInput* b7, SingleInput* b8,
                 SingleInput* b9, SingleInput* b10, SingleInput* b11, SingleInput* b12,
                 SingleInput* b13, SingleInput* b14, SingleInput* b15, SingleInput* b16,
                 SingleInput* b17, SingleInput* b18, SingleInput* b19, SingleInput* b20,
                 SingleInput* b21, SingleInput* b22, SingleInput* b23, SingleInput* b24,
                 SingleInput* b25, SingleInput* b26, SingleInput* b27, SingleInput* b28,
                 SingleInput* b29, SingleInput* b30, SingleInput* b31, SingleInput* b32);

   // destructor
   virtual ~VirpilMT50CM3() {};

   // Forward Backward Pivot */
   SingleInput forwardBackwardPivot;

   // Left Right pivot
   SingleInput leftRightPivot;

   // Twist
   SingleInput twist;

   // Forward Backward Translation
   SingleInput forwardBackwardTranslation;

   // Left/Right Translation
   SingleInput leftRightTranslation;

   // slider
   SingleInput slider;

   protected:

   // Buttons - lots of buttons
   SingleInput* anonButton1;
   SingleInput* anonButton2;
   SingleInput* anonButton3;
   SingleInput* anonButton4;
   SingleInput* anonButton5;
   SingleInput* anonButton6;
   SingleInput* anonButton7;
   SingleInput* anonButton8;
   SingleInput* anonButton9;
   SingleInput* anonButton10;
   SingleInput* anonButton11;
   SingleInput* anonButton12;
   SingleInput* anonButton13;
   SingleInput* anonButton14;
   SingleInput* anonButton15;
   SingleInput* anonButton16;
   SingleInput* anonButton17;
   SingleInput* anonButton18;
   SingleInput* anonButton19;
   SingleInput* anonButton20;
   SingleInput* anonButton21;
   SingleInput* anonButton22;
   SingleInput* anonButton23;
   SingleInput* anonButton24;
   SingleInput* anonButton25;
   SingleInput* anonButton26;
   SingleInput* anonButton27;
   SingleInput* anonButton28;
   SingleInput* anonButton29;
   SingleInput* anonButton30;
   SingleInput* anonButton31;
   SingleInput* anonButton32;

   /**
    * @brief provide common decoding for any grip attached to this base
    * 
    * @param data vector of bytes that is a report read from device
    */
   void decode(const std::vector<unsigned char>& data);

};

} // namespace

#endif
