#include "idf/HidDecoder.hh"
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace idf
{


HidDecoder::HidDecoder()
{
   init();
}


void HidDecoder::init()
{
   reports.clear();
   inputs.clear();
   bit_offset = 0;
   report_id = 0;
   usage_list.clear();
   state.report_size = 0;
   state.report_count = 0;
   state.usage_page = 0;
   state.usage_min = 0;
   state.usage_max = 0;
   state.logical_min = 0;
   state.logical_max = 0;
   state.physical_min = 0;
   state.physical_max = 0;
   state.units = 0;
   state.units_exp = 0;
   device_type = "Unknown";
   state_stack.clear();
   next_button = 1;
}


HidDecoded* HidDecoder::parseDescriptor(const std::vector<unsigned char> &descriptor)
{
   init();
   uint i = 0;

   while (i < descriptor.size()) {
      unsigned char prefix = descriptor[i];
      int size_code = prefix & 0x03;
      int type_code = (prefix >> 2) & 0x03;
      int tag_code = (prefix >> 4) & 0x0F;
      int data = 0;
      std::vector<unsigned char> data_bytes;

      int size = size_code;
      if (size_code == 3) {
            size = 4;
      }

      if (size > 0) {
            data_bytes = std::vector<unsigned char>(descriptor.begin() + i + 1, descriptor.begin() + i + 1 + size);
            data = 0;
            for (int j = 0; j < size; ++j) {
               data |= (data_bytes[j] << (j * 8));
            }
      }

      if (type_code == 0) { // Main
            decodeMainItem(tag_code);
      }
      else if (type_code == 1) { // Global
            decodeGlobalItem(tag_code, data, data_bytes);
      }
      else if (type_code == 2) { // Local
            decodeLocalItem(tag_code, data);
      }

      i += 1 + size;
   }

   // add final report to list
   reports.push_back({
      report_id,
      inputs,
      bit_offset / 8,
      report_id != 0
   });

   int maxReport = -1;
   for (HidReport rep : reports) {
      if (rep.inputs.size() > 0) {
         maxReport = std::max(maxReport, rep.bytes_count);
      }
   }

   HidDecoded* decoded = new HidDecoded();

   decoded->type = device_type;
   decoded->reports = reports;
   decoded->maxReportLength = maxReport;

   return decoded;
}


void HidDecoder::decodeGlobalItem(const int tag_code, int data, const std::vector<unsigned char> &data_bytes)
{
   switch(tag_code) {
   case GLOBAL_USAGE_PAGE:
      state.usage_page = data;
      break;

   case GLOBAL_LOGICAL_MINIMUM:
      state.logical_min = convertDataToInt(data_bytes, true);
      break;

   case GLOBAL_LOGICAL_MAXIMUM:
      state.logical_max = convertDataToInt(data_bytes, true);
      break;

   case GLOBAL_PHYSICAL_MINIMUM:
      state.physical_min = convertDataToInt(data_bytes, interpretSigned());
      break;

   case GLOBAL_PHYSICAL_MAXIMUM:
      state.physical_max = convertDataToInt(data_bytes, interpretSigned());
      break;

   case GLOBAL_UNIT_EXPONENT:
      state.units_exp = static_cast<int8_t>(data_bytes[0]);
      break;

   case GLOBAL_UNITS:
      state.units = data;
      if (data == 0)
      {
         state.units = 0;
         state.units_exp = 0;
         state.physical_min = 0;
         state.physical_max = 0;
      }
      break;

   case GLOBAL_REPORT_SIZE:
      state.report_size = data;
      break;

   case GLOBAL_REPORT_ID:
      if (report_id != 0)
      { // if not the 1st report, save inputs to a report
         reports.push_back({report_id,
                              inputs,
                              bit_offset / 8,
                              true});
         inputs.clear();
      }

      bit_offset = 8;
      report_id = data;
      break;

   case GLOBAL_REPORT_COUNT:
      state.report_count = data;
      break;

   case GLOBAL_PUSH:
      state_stack.push_back(state);
      break;

   case GLOBAL_POP:
      if (!state_stack.empty())
      {
         HIDState tmp = state_stack.back();
         state.usage_page = tmp.usage_page;
         state.usage_min = tmp.usage_min;
         state.usage_max = tmp.usage_max;
         state.report_size = tmp.report_size;
         state.report_count = tmp.report_count;
         state.logical_min = tmp.logical_min;
         state.logical_max = tmp.logical_max;
         state.physical_min = tmp.physical_min;
         state.physical_max = tmp.physical_max;
         state.units = tmp.units;
         state.units_exp = tmp.units_exp;
         state_stack.pop_back();
      }
      break;

   default:
      break;
   }
}


void HidDecoder::decodeLocalItem(const int tag_code, const int data)
{
   switch(tag_code) {
   case LOCAL_USAGE:
      if (data < USAGE_X){
         if (device_type == "Unknown") {
            device_type = usageName(data);
         }
      }
      else {
         usage_list.push_back(data);
      }
      break;

   case LOCAL_MINIMUM:
      state.usage_min = data;
      break;

   case LOCAL_MAXIMUM:
      state.usage_max = data;
      break;

   case LOCAL_DESIGNATOR_IDX: // not implemented
   case LOCAL_DESIGNATOR_MINIMUM: // not implemented
   case LOCAL_DESIGNATOR_MAXIMUM: // not implemented
   case LOCAL_STRING_IDX: // not implemented
   case LOCAL_STRING_MINIMUM: // not implemented
   case LOCAL_STRING_MAXIMUM: // not implemented
   case LOCAL_DELIMITER: // not implemented
   default: break; // items not yet defined
   }
}


void HidDecoder::decodeMainItem(const int tag_code)
{
   switch(tag_code) {
   case MAIN_INPUT:
      createInputs();
      break;

   case MAIN_OUTPUT:
   case MAIN_FEATURE: // Outputs and Features are not supported
      usage_list.clear();
      state.usage_min = 0;
      state.usage_max = 0;
      break;

   case MAIN_COLLECTION: // not implemented
   case MAIN_END_COLLECTION: // not implemented
   default: // items not yet defined
      break;
   }
}

void HidDecoder::createInputs()
{
   std::vector<int> expanded_usages;

   if (state.usage_min != 0 && state.usage_max != 0)
   {
      for (int j = state.usage_min; j <= state.usage_max; ++j)
      {
         expanded_usages.push_back(j);
      }
   }
   else if (!usage_list.empty()) {
      expanded_usages = usage_list;
   }

   for (uint j = 0; j < state.report_count; ++j) {
      std::string name;
      u_int8_t usage = 0;
      int btn_num = -1;
      if (state.usage_page == 0x01 && j < expanded_usages.size()) {
         usage = expanded_usages[j];
         name = usageName(usage);
      }
      else if (state.usage_page == USAGE_BUTTON && j < expanded_usages.size()) {
         usage = USAGE_BUTTON;
         btn_num = next_button++;
         name = "Button " + std::to_string(btn_num);
      }
      else if (state.usage_page == 0x01 && expanded_usages.size() == 1) {
         usage = expanded_usages[0];
         name = usageName(usage);
      }
      else {
         name = "Padding";
      }

      int start_bit = bit_offset;
      int end_bit = bit_offset + state.report_size - 1;

      int tmp_phys_min = state.physical_min;
      int tmp_phys_max = state.physical_max;

      // when physical min/max are not set, default to logical
      if (state.physical_min == 0) tmp_phys_min = state.logical_min;
      if (state.physical_max == 0) tmp_phys_max = state.logical_max;

      inputs.push_back({  usage,
                           name,
                           start_bit,
                           end_bit,
                           state.logical_min,
                           state.logical_max,
                           tmp_phys_min,
                           tmp_phys_max,
                           state.units,
                           state.units_exp,
                           btn_num});

      bit_offset += state.report_size;
   }

   usage_list.clear();
   state.usage_min = 0;
   state.usage_max = 0;
}

bool HidDecoder::interpretSigned() const
{
   return state.logical_max < 0 || state.logical_min < 0;
}


int HidDecoder::convertDataToInt(const std::vector<unsigned char> &data, const bool isSigned) const
{
   u_int32_t value = 0;

   for (uint i = 0; i < data.size(); ++i) {
      value += (data[i] << 8*i);
   }

   if (!isSigned) return value;

   switch (data.size()) {
   case 1:
      if (value >= pow(2,7)) return static_cast<int8_t>(value);
      break;
   case 2:
      if (value >= pow(2,15)) return static_cast<int16_t>(value);
      break;
   case 4:
      if (value >= pow(2,31)) return static_cast<int32_t>(value);
      break;
   }
   return value;
}


void HidDecoder::printDecodedInfo(const HidDecoded decoded)
{
   std::ostringstream ss;
   ss << "Device Type: " << decoded.type << "\n";
   for (HidReport report : decoded.reports) {
      ss << "Report: " << report.id << "  (" << report.bytes_count << " bytes)\n";
      if (report.id != 0) {
         ss << "   Report ID       bits      0:7     value:      " << report.id << "\n";
      }
      for(HidInput input : report.inputs) {
         ss << "   " << std::setfill(' ') << std::setw(15) << std::left << input.name;
         if (input.start_bit == input.end_bit) {
            ss << " bit     " << std::setw(5) << std::right << input.start_bit << "     range:  ";
            ss << std::setw(5) << std::right << input.logical_min << ":";
            ss << std::left << input.logical_max << "\n";
         }
         else {
            ss << " bits  " << std::setw(5) << std::right << input.start_bit << ":";
            ss << std::setw(5) << std::left << input.end_bit;
            ss << " range:  ";
            ss << std::setw(5) << std::right << input.logical_min << ":";
            ss << std::setw(5) << std::left << input.logical_max << "   ";
            ss << std::setw(5) << std::right << input.physical_min << ":";
            ss << std::setw(5) << std::left << input.physical_max << "\n";
         }
      }
      ss << "\n";
   }
   printf(ss.str().c_str());
}


u_int64_t HidDecoder::extractValue(const HidInput& input, const std::vector<unsigned char>& data, const bool print) const
{
   if (!isUsageKnown(input.usage)) return 0;
   int startByte = input.start_bit / 8;
   int startBit =  input.start_bit % 8;
   int endByte = input.end_bit / 8;
   u_int64_t temp = 0; // while HID theoretically allows an item to be 255 bytes, it is
   u_int64_t mask = 1; // very unlikely that a single HC input will need >16 bits

   mask = (mask << (input.end_bit - input.start_bit +1)) - 1;

   // stack bytes in reverse to get continuous bits
   for(int i = endByte; i >= startByte; --i) {
      temp = temp << 8;
      temp |= data[i];
   }

   temp = (temp >> startBit) & mask;

   if (print) {
      int endBit = input.end_bit % 8;
      std::string paddedName = input.name;
      std::string endBitsStr = std::to_string(endByte) + "[" + std::to_string(endBit) + "]";
      paddedName.append(14 - paddedName.length(), ' ');
      endBitsStr.append(10 - endBitsStr.length(), ' ');
      std::cout << "   " << paddedName \
         << std::setw(4) << std::right << startByte << '[' << std::setw(0) << startBit << "]-" \
         << endBitsStr \
         << "mask(0x" << std::setw(4) << std::setfill('0') << std::hex << mask << ")  = " \
         << std::setfill(' ') << std::setw(7) << std::dec << temp << std::endl;

   }
   return temp;
}

bool HidDecoder::isUsageKnown(const uint usage ) const
{
   switch(usage) {
      case(USAGE_POINTER):
      case(USAGE_JOYSTICK):
      case(USAGE_GAMEPAD):
      case(USAGE_MULTIAXIS):
      case(USAGE_BUTTON):
      case(USAGE_X):
      case(USAGE_Y):
      case(USAGE_Z):
      case(USAGE_RX):
      case(USAGE_RY):
      case(USAGE_RZ):
      case(USAGE_SLIDER):
      case(USAGE_DIAL):
      case(USAGE_WHEEL):
      case(USAGE_HAT):
      case(USAGE_START):
      case(USAGE_SELECT):
         return true; break;
      default:
         return false; break;
   }
}

std::string HidDecoder::usageName(const uint usage) const
{
   if (!isUsageKnown(usage)) return "Unknown";

   return usage_names.at(usage);
}

} // namespace
