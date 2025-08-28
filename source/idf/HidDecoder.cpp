#include "idf/HidDecoder.hh"
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace idf
{


HidDecoder::HidDecoder() {
   init();
}


void HidDecoder::init() {
   reports_.clear();
   inputs_.clear();
   bit_offset_ = 0;
   report_id_ = 0;
   usage_list_.clear();
   current_.report_size = 0;
   current_.report_count = 0;
   current_.usage_page = 0;
   current_.usage_min = 0;
   current_.usage_max = 0;
   current_.logical_min = 0;
   current_.logical_max = 0;
   current_.physical_min = 0;
   current_.physical_max = 0;
   current_.units = 0;
   current_.units_exp = 0;
   device_type_ = "Unknown";
   state_stack_.clear();
   button_base_ = 1;
}


HidDecoded HidDecoder::parseDescriptor(const std::vector<unsigned char> &descriptor)
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
   reports_.push_back({
      report_id_,
      inputs_,
      bit_offset_ / 8,
      report_id_ != 0
   });

   int maxReport = -1;
   for (HidReport rep : reports_) {
      if (rep.inputs.size() > 0) {
         maxReport = std::max(maxReport, rep.bytes_count);
      }
   }

   return {device_type_, reports_, maxReport};
}


void HidDecoder::decodeGlobalItem(const int tag_code, int data, const std::vector<unsigned char> &data_bytes)
{
   if (tag_code == 0x0) {  // Usage Page
      current_.usage_page = data;
   }
   else if (tag_code == 0x1) {  // Logical Minimum
      current_.logical_min = convertDataToInt(data_bytes, true);
   }
   else if (tag_code == 0x2) {  // Logical Maximum
      current_.logical_max = convertDataToInt(data_bytes, true);
   }
   else if (tag_code == 0x3) {  // Physical Minimum
      current_.physical_min = convertDataToInt(data_bytes, interpretSigned());
   }
   else if (tag_code == 0x4) {  // Physical Maximum
      current_.physical_max = convertDataToInt(data_bytes, interpretSigned());
   }
   else if (tag_code == 0x5) {  // Unit exponent
      current_.units_exp = static_cast<int8_t>(data_bytes[0]);
   }
   else if (tag_code == 0x6) {  // Units
      current_.units = data;
      if (data == 0)
      {
         current_.units = 0;
         current_.units_exp = 0;
         current_.physical_min = 0;
         current_.physical_max = 0;
      }
   }
   else if (tag_code == 0x7) {  // Report Size
      current_.report_size = data;
   }
   else if (tag_code == 0x8) {  // Report ID
      if (report_id_ != 0)
      { // if not the 1st report, save inputs to a report
         reports_.push_back({report_id_,
                              inputs_,
                              bit_offset_ / 8,
                              true});
         inputs_.clear();
      }

      bit_offset_ = 8;
      report_id_ = data;
   }
   else if (tag_code == 0x9) {  // Report Count
      current_.report_count = data;
   }
   else if (tag_code == 0xA) {  // Push
      state_stack_.push_back(current_);
   }
   else if (tag_code == 0xB) {  // Pop
      if (!state_stack_.empty())
      {
         HIDState tmp = state_stack_.back();
         current_.usage_page = tmp.usage_page;
         current_.usage_min = tmp.usage_min;
         current_.usage_max = tmp.usage_max;
         current_.report_size = tmp.report_size;
         current_.report_count = tmp.report_count;
         current_.logical_min = tmp.logical_min;
         current_.logical_max = tmp.logical_max;
         current_.physical_min = tmp.physical_min;
         current_.physical_max = tmp.physical_max;
         current_.units = tmp.units;
         current_.units_exp = tmp.units_exp;
         state_stack_.pop_back();
      }
   }
}


void HidDecoder::decodeLocalItem(const int tag_code, const int data)
{
   if (tag_code == 0x0) {  // Usage
      if (data < USAGE_X) {
         if (device_type_ == "Unknown") {
            device_type_ = usage_names_.at(data);
         }
      }
      else {
         usage_list_.push_back(data);
      }
   }
   else if (tag_code == 0x1) {  // Usage Minimum
      current_.usage_min = data;
   }
   else if (tag_code == 0x2) {  // Usage Maximum
      current_.usage_max = data;
   }
}


void HidDecoder::decodeMainItem(const int tag_code)
{
   if (tag_code == 0x8) {  // Create Input(s) from usage list HIDState information
      std::vector<int> expanded_usages;
      if (current_.usage_min != 0 && current_.usage_max != 0)
      {
         for (int j = current_.usage_min; j <= current_.usage_max; ++j)
         {
            expanded_usages.push_back(j);
         }
      }
      else if (!usage_list_.empty()) {
         expanded_usages = usage_list_;
      }

      for (uint j = 0; j < current_.report_count; ++j) {
         std::string name;
         u_int8_t usage = 0;
         int btn_num = -1;
         if (current_.usage_page == 0x01 && j < expanded_usages.size()) {
            usage = expanded_usages[j];
            if (usage_names_.count(usage)) name = usage_names_.at(usage);
            else name = "Unknown";
         }
         else if (current_.usage_page == USAGE_BUTTON && j < expanded_usages.size()) {
            usage = USAGE_BUTTON;
            btn_num = button_base_;
            name = "Button " + std::to_string(button_base_++);
         }
         else if (current_.usage_page == 0x01 && expanded_usages.size() == 1) {
            usage = expanded_usages[0];
            if (usage_names_.count(usage)) name = usage_names_.at(usage);
            else name = "Unknown";
         }
         else {
            name = "Padding";
         }

         int start_bit = bit_offset_;
         int end_bit = bit_offset_ + current_.report_size - 1;

         int tmp_phys_min = current_.physical_min;
         int tmp_phys_max = current_.physical_max;
         if (current_.physical_min == 0) {
            tmp_phys_min = current_.logical_min;
         }
         if (current_.physical_max == 0) {
            tmp_phys_max = current_.logical_max;
         }

         inputs_.push_back({usage,
                              name,
                              start_bit,
                              end_bit,
                              current_.logical_min,
                              current_.logical_max,
                              tmp_phys_min,
                              tmp_phys_max,
                              current_.units,
                              current_.units_exp,
                              btn_num});

         bit_offset_ += current_.report_size;
      }

      usage_list_.clear();
      current_.usage_min = 0;
      current_.usage_max = 0;
   }
   else if (tag_code == 0x9 || tag_code == 0x0B) { // Output or Feature
      usage_list_.clear();
      current_.usage_min = 0;
      current_.usage_max = 0;
   }
}


bool HidDecoder::interpretSigned() const {
   return current_.logical_max < 0 || current_.logical_min < 0;
}


int HidDecoder::convertDataToInt(const std::vector<unsigned char> &data, const bool isSigned) const {
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


void HidDecoder::printDecodedInfo(const HidDecoded decoded) {
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


u_int64_t HidDecoder::extractValue(const HidInput& input, const std::vector<unsigned char>& data, const bool print) const {
   if (!usage_names_.count(input.usage)) return 0;
   int startByte = input.start_bit / 8;
   int startBit =  input.start_bit % 8;
   int endByte = input.end_bit / 8;
   u_int64_t temp = 0; // while HID theoretically allows an item to be 255 bytes, it is
   u_int64_t mask = 1; // very unlikely that a single HC input will need even 4 bytes

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

} // namespace
