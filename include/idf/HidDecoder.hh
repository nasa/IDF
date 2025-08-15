/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/HidDecoder.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/HidDecoder.cpp}
 */

#ifndef HID_DECODER_HH
#define HID_DECODER_HH

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "hidapi/hidapi/hidapi.h"

namespace idf
{

struct HidInput
{
   u_int8_t usage;
   std::string name;
   int start_bit;
   int end_bit;
   int logical_min;
   int logical_max;
   int physical_min;
   int physical_max;
   int units;
   int units_exp;
   int button_num;
};

struct HidReport
{
   int id;
   std::vector<HidInput> inputs;
   int bytes_count;
   bool has_report_byte;
};

struct HidDecoded
{
   std::string type;
   std::vector<HidReport> reports;
   int maxReportLength;
};

enum HidUsages {
   USAGE_POINTER   = 0x01,
   USAGE_JOYSTICK  = 0x04,
   USAGE_GAMEPAD   = 0x05,
   USAGE_MULTIAXIS = 0x08,
   USAGE_BUTTON    = 0x09,
   USAGE_X         = 0x30,
   USAGE_Y         = 0x31,
   USAGE_Z         = 0x32,
   USAGE_RX        = 0x33,
   USAGE_RY        = 0x34,
   USAGE_RZ        = 0x35,
   USAGE_SLIDER    = 0x36,
   USAGE_DIAL      = 0x37,
   USAGE_WHEEL     = 0x38,
   USAGE_HAT       = 0x39,
   USAGE_START     = 0x3D,
   USAGE_SELECT    = 0x3E,
};

class HidDecoder
{

public:
   HidDecoder();

   /**
    * @brief parse a list of @a HidReports with @a HidInputs from an HID
    * Report Descriptor. Only @a Input items are kept. @a Output and
    * @a feature items are discarded
    *
    * @param descriptor binary HID report descriptor.
    * @return HidDecoded struct with a list of HidReports and some metadata
    */
   HidDecoded parseDescriptor(const std::vector<unsigned char>& descriptor);


   /**
    * @brief Print out decoded information to stdout
    *
    * @param decoded an @a HidDecoded struct
    */
   static void printDecodedInfo(HidDecoded decoded);


   /**
    * @brief extract the appropriate binary value from the data for a given HidInput
    *
    * @param input HidInput retrieved from parsing HID report descriptor
    * @param data data that was read in from device
    * @return u_int64_t raw binary data extracted from device.
    */
   u_int64_t extractValue(const HidInput& input, const std::vector<unsigned char>& data);


   const std::map<u_int8_t, std::string> usage_names_ = {
      {USAGE_POINTER, "Pointer"},
      {USAGE_JOYSTICK, "Joystick"},
      {USAGE_GAMEPAD, "Gamepad"},
      {USAGE_MULTIAXIS, "Multi-axis Controller"},
      {USAGE_BUTTON, "Button"},
      {USAGE_X, "X"},
      {USAGE_Y, "Y"},
      {USAGE_Z, "Z"},
      {USAGE_RX, "Rx"},
      {USAGE_RY, "Ry"},
      {USAGE_RZ, "Rz"},
      {USAGE_SLIDER, "Slider"},
      {USAGE_DIAL, "Dial"},
      {USAGE_WHEEL, "Wheel"},
      {USAGE_HAT, "Hat switch"},
      {USAGE_START, "Start"},
      {USAGE_SELECT, "Select"},
   };


private:
   void init();
   int convertDataToInt(const std::vector<unsigned char> &data, bool isSigned);
   bool interpretSigned();
   void decodeGlobalItem(int tag_code, int data, const std::vector<unsigned char>& data_bytes);
   void decodeLocalItem(int tag_code, int data);
   void decodeMainItem(int tag_code);

   struct HIDState {
      uint report_size;
      uint report_count;
      int usage_page;
      int usage_min;
      int usage_max;
      int logical_min;
      int logical_max;
      int physical_min;
      int physical_max;
      int units;
      int units_exp;
   };

   int vendorId_;
   int productId_;

   std::string device_type_ = "Unknown";
   std::vector<HidReport> reports_;
   std::vector<HidInput> inputs_;
   int bit_offset_ = 0;
   int report_id_ = 0;
   std::vector<int> usage_list_;

   HIDState current_;
   std::vector<HIDState> state_stack_;
   int button_base_ = 1;

}; // HidDecoder

} // namespace

#endif
