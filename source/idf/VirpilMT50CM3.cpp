#include "idf/VirpilMT50CM3.hh"
#include <cstdio>

namespace idf {

VirpilMT50CM3::VirpilMT50CM3(SingleInput* b1, SingleInput* b2, SingleInput* b3, SingleInput* b4,
                             SingleInput* b5, SingleInput* b6, SingleInput* b7, SingleInput* b8,
                             SingleInput* b9, SingleInput* b10, SingleInput* b11, SingleInput* b12,
                             SingleInput* b13, SingleInput* b14, SingleInput* b15, SingleInput* b16,
                             SingleInput* b17, SingleInput* b18, SingleInput* b19, SingleInput* b20,
                             SingleInput* b21, SingleInput* b22, SingleInput* b23, SingleInput* b24,
                             SingleInput* b25, SingleInput* b26, SingleInput* b27, SingleInput* b28,
                             SingleInput* b29, SingleInput* b30, SingleInput* b31, SingleInput* b32) :
   forwardBackwardPivot(0, 60000, 30000),
   leftRightPivot(0, 60000, 30000),
   twist(0, 60000, 30000),
   forwardBackwardTranslation(0, 60000, 30000),
   leftRightTranslation(0, 60000, 30000),
   slider(0, 60000, 0) {
      anonButton1 = b1; anonButton2 = b2; anonButton3 = b3; anonButton4 = b4;
      anonButton5 = b5; anonButton6 = b6; anonButton7 = b7; anonButton8 = b8;
      anonButton9 = b9; anonButton10 = b10; anonButton11 = b11; anonButton12 = b12;
      anonButton13 = b13; anonButton14 = b14; anonButton15 = b15; anonButton16 = b16;
      anonButton17 = b17; anonButton18 = b18; anonButton19 = b19; anonButton20 = b20;
      anonButton21 = b21; anonButton22 = b22; anonButton23 = b23; anonButton24 = b24;
      anonButton25 = b25; anonButton26 = b26; anonButton27 = b27; anonButton28 = b28;
      anonButton29 = b29; anonButton30 = b30; anonButton31 = b31; anonButton32 = b32;
   }

void VirpilMT50CM3::decode(const std::vector<unsigned char>& data) {
   if (data[0] != 1) return;

   leftRightPivot.setValue(((unsigned)data[2] << 8) | data[1]);
   forwardBackwardPivot.setValue(((unsigned)data[4] << 8) | data[3]);
   forwardBackwardTranslation.setValue(((unsigned)data[6] << 8) | data[5]);
   leftRightTranslation.setValue(((unsigned)data[8] << 8) | data[7]);
   slider.setValue(((unsigned)data[10] << 8) | data[9]);
   twist.setValue(((unsigned)data[12] << 8) | data[11]);
   anonButton1->setValue(data[21] & 0x1);
   anonButton2->setValue((data[21] >> 1) & 0x1);
   anonButton3->setValue((data[21] >> 2) & 0x1);
   anonButton4->setValue((data[21] >> 3) & 0x1);
   anonButton5->setValue((data[21] >> 4) & 0x1);
   anonButton6->setValue((data[21] >> 5) & 0x1);
   anonButton7->setValue((data[21] >> 6) & 0x1);
   anonButton8->setValue((data[21] >> 7) & 0x1);
   anonButton9->setValue(data[22] & 0x1);
   anonButton10->setValue((data[22] >> 1) & 0x1);
   anonButton11->setValue((data[22] >> 2) & 0x1);
   anonButton12->setValue((data[22] >> 3) & 0x1);
   anonButton13->setValue((data[22] >> 4) & 0x1);
   anonButton14->setValue((data[22] >> 5) & 0x1);
   anonButton15->setValue((data[22] >> 6) & 0x1);
   anonButton16->setValue((data[22] >> 7) & 0x1);
   anonButton17->setValue(data[23] & 0x1);
   anonButton18->setValue((data[23] >> 1) & 0x1);
   anonButton19->setValue((data[23] >> 2) & 0x1);
   anonButton20->setValue((data[23] >> 3) & 0x1);
   anonButton21->setValue((data[23] >> 4) & 0x1);
   anonButton22->setValue((data[23] >> 5) & 0x1);
   anonButton23->setValue((data[23] >> 6) & 0x1);
   anonButton24->setValue((data[23] >> 7) & 0x1);
   anonButton25->setValue(data[24] & 0x1);
   anonButton26->setValue((data[24] >> 1) & 0x1);
   anonButton27->setValue((data[24] >> 2) & 0x1);
   anonButton28->setValue((data[24] >> 3) & 0x1);
   anonButton29->setValue((data[24] >> 4) & 0x1);
   anonButton30->setValue((data[24] >> 5) & 0x1);
   anonButton31->setValue((data[24] >> 6) & 0x1);
   anonButton32->setValue((data[24] >> 7) & 0x1);
}

} // namespace idf