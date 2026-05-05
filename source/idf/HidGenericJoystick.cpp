#include "idf/HidGenericJoystick.hh"

namespace idf {

HidGenericJoystick::HidGenericJoystick(const int vendor, const int product, const int interface) :
   HidDevice(vendor, product, interface)
   {
      init();
   }

HidGenericJoystick::HidGenericJoystick(const std::string& devPath) :
   HidDevice(devPath)
   {
      init();
   }

/**
 * @brief Initialize the joystick based on the decoded HID Report Descriptor
 */
void HidGenericJoystick::init()
{
   for( HidReport report : descriptor.reports) {
      for (HidInput input : report.inputs) {
         switch(input.usage) {
            case USAGE_BUTTON:
               if (input.button_num == 1)
               {
                  buttons.push_back(&trigger);
               }
               else
               {
                  buttons.push_back(new SingleInput(0,1));
               }
               break;

            case USAGE_X:
               // legacy dictates that X is a pivot even though it is a liner axis
               leftRightPivot.configure(input.logical_min, input.logical_max);
               break;

            case USAGE_Y:
               // legacy dictates that Y is a pivot even though it is a liner axis
               forwardBackwardPivot.configure(input.logical_min, input.logical_max);
               break;

            case USAGE_Z:
               // Up to the manufacturer whether twist is Z or RZ, but the
               // norm seems to be that if Z exists it is the twist axis
               useZForTwist = true;
               twist.configure(input.logical_min, input.logical_max);
               break;

            case USAGE_RX:
               rxExists = true;
               leftRightTranslation.configure(input.logical_min, input.logical_max);
               break;

            case USAGE_RY:
               ryExists = true;
               forwardBackwardTranslation.configure(input.logical_min, input.logical_max);
               break;

            case USAGE_WHEEL:
               wheelExists = true;
               wheel.configure(input.logical_min, input.logical_max);
               break;

         }
      }
   }
}

/**
 * @brief decode data that was read from device using the decoded Report Descriptor
 *
 * @param data HID Report data read from device
 */
void HidGenericJoystick::decode(const std::vector<unsigned char>& data)
{
   for (HidReport r : descriptor.reports) {
      if (!r.has_report_byte || (r.has_report_byte && static_cast<int>(data[0]) == r.id)) {
         for(HidInput input : r.inputs) {

            u_int64_t value = decoder.extractValue(input, data);

            switch (input.usage) {
               case USAGE_BUTTON:
                  try {
                     buttons.at(input.button_num - 1)->setValue(value);
                  }
                  catch (std::out_of_range & e) {}
                  break;

               case USAGE_X:
                  leftRightPivot.setValue(value);
                  break;

               case USAGE_Y:
                  forwardBackwardPivot.setValue(value);
                  break;

               case USAGE_Z:
                  twist.setValue(value);
                  break;

               case USAGE_RX:
                  leftRightTranslation.setValue(value);
                  break;

               case USAGE_RY:
                  forwardBackwardTranslation.setValue(value);
                  break;

               case USAGE_RZ:
                  if (!useZForTwist) twist.setValue(value);
                  break;

               case USAGE_SLIDER:
                  slider.setValue(value);
                  break;

               case USAGE_WHEEL:
                  wheel.setValue(value);
                  break;

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

            } // switch
         } // for input
      } // if correct report
   } // for report
}

} // namespace idf
