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

struct HidDescriptor
{
   unsigned short vendor;
   unsigned short product;
   unsigned short interface;
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

enum MainItemTag {
   MAIN_INPUT           = 0x8,
   MAIN_OUTPUT          = 0x9,
   MAIN_COLLECTION      = 0xA,
   MAIN_FEATURE         = 0xB,
   MAIN_END_COLLECTION  = 0xC,
};

enum GlobalItemTag {
   GLOBAL_USAGE_PAGE       = 0x0,
   GLOBAL_LOGICAL_MINIMUM  = 0x1,
   GLOBAL_LOGICAL_MAXIMUM  = 0x2,
   GLOBAL_PHYSICAL_MINIMUM = 0x3,
   GLOBAL_PHYSICAL_MAXIMUM = 0x4,
   GLOBAL_UNIT_EXPONENT    = 0x5,
   GLOBAL_UNITS            = 0x6,
   GLOBAL_REPORT_SIZE      = 0x7,
   GLOBAL_REPORT_ID        = 0x8,
   GLOBAL_REPORT_COUNT     = 0x9,
   GLOBAL_PUSH             = 0xA,
   GLOBAL_POP              = 0xB,
};

enum LocalItemTags {
   LOCAL_USAGE              = 0x0,
   LOCAL_MINIMUM            = 0x1,
   LOCAL_MAXIMUM            = 0x2,
   LOCAL_DESIGNATOR_IDX     = 0x3,
   LOCAL_DESIGNATOR_MINIMUM = 0x4,
   LOCAL_DESIGNATOR_MAXIMUM = 0x5,
   LOCAL_STRING_IDX         = 0x7,
   LOCAL_STRING_MINIMUM     = 0x8,
   LOCAL_STRING_MAXIMUM     = 0x9,
   LOCAL_DELIMITER          = 0xA,
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
    * @param descriptor binary HID Report Descriptor.
    * @return HidDescriptor struct with a list of HidReports and some metadata
    */
   HidDescriptor* parseDescriptor(const std::vector<unsigned char>& descriptor);


   /**
    * @brief Print out decoded descriptor information to stdout
    *
    * @param describer an @a HidDescriptor struct
    */
   static void printDecodedInfo(const HidDescriptor describer);


   /**
    * @brief extract the appropriate binary value from the data for a given HidInput
    *
    * @param input HidInput retrieved from parsing HID report descriptor
    * @param data data that was read in from device
    * @return u_int64_t raw binary data extracted from device.
    */
   u_int64_t extractValue(const HidInput& input, const std::vector<unsigned char>& data, const bool print = false) const;

   bool isUsageKnown(const uint usage) const;
   std::string usageName(const uint usage) const;

private:
   void init();
   void decodeGlobalItem(const int tag_code, const int data, const std::vector<unsigned char>& data_bytes);
   void decodeLocalItem(const int tag_code, const int data);
   void decodeMainItem(const int tag_code);
   void createInputs();
   int convertDataToInt(const std::vector<unsigned char> &data, const bool isSigned) const;
   bool interpretSigned() const;

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

   std::string device_type = "Unknown";
   std::vector<HidReport> reports;
   std::vector<HidInput> inputs;
   int bit_offset = 0;
   int report_id = 0;
   std::vector<int> usage_list;

   HIDState state;
   std::vector<HIDState> state_stack;
   int next_button = 1;

   const std::map<u_int8_t, std::string> usage_names = {
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

}; // HidDecoder

} // namespace

#endif
