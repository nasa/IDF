#include "idf/HidGenericJoystick.hh"

namespace idf {


HidGenericJoystick::HidGenericJoystick(const int vendor, const int product, const int interface) :
   HidDevice(vendor, product, interface) {
      // addIdentification(Identification(vendor, product, interface));
      // configure inputs and instantiate list of buttons
      for( HidReport report : decoded.reports) {
         for (HidInput input : report.inputs) {
            switch(input.usage) {
            case USAGE_BUTTON:
               if (input.button_num == 1)
                  buttons.push_back(&trigger);
               else
                  buttons.push_back(new SingleInput(0,1));
               break;
            case USAGE_X:
               leftRightPivot.configure(input.logical_min, input.logical_max);
               break;
            case USAGE_Y:
               forwardBackwardPivot.configure(input.logical_min, input.logical_max);
               break;
            case USAGE_Z:
               useZForTwist = true;
               twist.configure(input.logical_min, input.logical_max);
               break;
            }
         }
      }
   }


void HidGenericJoystick::decode(const std::vector<unsigned char>& data) {
   for (HidReport r : decoded.reports) {
      if (!r.has_report_byte || (r.has_report_byte && static_cast<int>(data[0]) == r.id)) {
         for( HidInput input : r.inputs) {
            u_int64_t value = decoder.extractValue(input, data);
            switch (input.usage) {
               case USAGE_BUTTON:
                  try {
                     buttons.at(input.button_num - 1)->setValue(value);
                  }
                  catch (std::out_of_range & e) {}
                  break;
               case USAGE_X:
                  leftRightPivot.setValue(value); break;
               case USAGE_Y:
                  forwardBackwardPivot.setValue(value); break;
               case USAGE_Z:
                  twist.setValue(value); break;
               case USAGE_RZ:
                  if (!useZForTwist) twist.setValue(value);
                  break;
               case USAGE_SLIDER:
                  slider.setValue(value); break;
               case USAGE_HAT:
                  int hat = value - input.logical_min;
                  HatNorth.setValue(hat == 0);
                  HatNorthEast.setValue(hat == 1);
                  HatEast.setValue(hat == 2);
                  HatSouthEast.setValue(hat == 3);
                  HatSouth.setValue(hat == 4);
                  HatSouthWest.setValue(hat == 5);
                  HatWest.setValue(hat == 6);
                  HatNorthWest.setValue(hat == 7);
                  break;
            }
         }
      }
   }
}

} // namespace idf
