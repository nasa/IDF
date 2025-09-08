#include <algorithm>
#include <cstring>
#include <cwchar>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <iomanip>
#include <errno.h>
#include "hidapi/hidapi/hidapi.h"
#include "idf/HidDecoder.hh"

static volatile bool keepReading = true;

void interruptHandler(int unused){
    keepReading = false;
}

int main(int argc, char **args) {

    signal(SIGINT, interruptHandler);

    int result = hid_init();
    if (result < 0) {
        printf("Failed to initialize HID library.\n");
        return -1;
    }

    struct hid_device_info* enumerationHead = hid_enumerate(0, 0);
    struct hid_device_info * deviceInfo;
    size_t serialLength = std::wcslen(L"Serial #");
    size_t vendorLength = std::wcslen(L"Vendor");
    size_t pathLength = std::strlen("Path");
    for (deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        serialLength = std::max(serialLength, wcslen(deviceInfo->serial_number));
        vendorLength = std::max(vendorLength, wcslen(deviceInfo->manufacturer_string));
        pathLength = std::max(pathLength, strlen(deviceInfo->path));
    }

    printf("\nNOTE: If running as non-root, you must have udev rules in place allowing access to usb devices.\n\n");
    printf("Index  %-*s  Vendor ID  Product ID  %-*ls  Interface #  %-*ls  Product\n", static_cast<int>(pathLength),
	   "Path", static_cast<int>(serialLength), L"Serial #", static_cast<int>(vendorLength), L"Vendor");

    int count = 0;
    for (deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next, ++count) {
        printf("%5d  %-*s  0x%04hX     0x%04hX      %-*ls  %11d  %-*ls  %ls\n", count,
          static_cast<int>(pathLength), deviceInfo->path,
          deviceInfo->vendor_id, deviceInfo->product_id,
          static_cast<int>(serialLength), deviceInfo->serial_number,
          deviceInfo->interface_number,
          static_cast<int>(vendorLength), deviceInfo->manufacturer_string,
          deviceInfo->product_string);
    }

    int selection = -1;
    printf("\n");

    while (selection < 0 || selection > count - 1) {
        char buffer[1024];
        printf("Select a device to listen to: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &selection);
    }

    deviceInfo = enumerationHead;
    for (count = 0; count < selection; ++count) {
        deviceInfo = deviceInfo->next;
    }

    hid_device* device = hid_open_path(deviceInfo->path);
    if (!device) {
        perror("Failed to open device");
        return -1;
    }

    hid_free_enumeration(enumerationHead);

    hid_set_nonblocking(device, 1);

    unsigned char report[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
    int descriptor_size = hid_get_report_descriptor(device, report, sizeof(report));

    if (descriptor_size < 0) {
        perror("Error reading HID Report Descriptor from device");
        return -1;
    }

    std::vector<unsigned char> descriptor(report, report + descriptor_size);
    std::vector<unsigned char> dataVect;

    idf::HidDecoder decoder;
    idf::HidDecoded devDecoded = *decoder.parseDescriptor(descriptor);

    unsigned char readTest[devDecoded.maxReportLength];
    unsigned char data[devDecoded.maxReportLength];

    decoder.printDecodedInfo(devDecoded);

    std::cout << "Press <Enter> to start decoding..." << std::endl;
    std::cin.ignore();

    while (keepReading) {
        int bytesRead = 0;
        int prevBytesRead = 0;
        do {
            bytesRead = hid_read(device, readTest, sizeof(readTest));
            if (bytesRead > 0) {
                memcpy(&data, &readTest, sizeof(data));
                prevBytesRead = bytesRead;
            }
        } while (bytesRead > 0);

        if (bytesRead < 0) {
            perror("Error reading from device");
            if (errno == EINTR) keepReading = false;
            else return -1;
        }
        else {

            dataVect.clear();
            dataVect.assign(data, data + prevBytesRead);

            // attempt to decode

            std::string btnStr = "";
            int btnStart = -1;
            int btnCnt = 0;
            int rows = 0;

            for (idf::HidReport r : devDecoded.reports) {
                if (!r.has_report_byte || (r.has_report_byte && static_cast<int>(data[0]) == r.id)) {
                    printf("\x1b[39;49mDecode report (%d) values:\n", r.id);
                    ++rows;
                    for( idf::HidInput input : r.inputs) {
                        if (input.name != "Unknown") {

                            // cluster buttons together for easier reading
                            // while keeping them in order
                            if (input.usage == idf::USAGE_BUTTON) {

                                if (btnCnt == 0) {
                                    btnStart = input.button_num;
                                }
                                else if (btnCnt == 4) btnStr.append(" ");

                                u_int64_t tmp = decoder.extractValue(input, dataVect, false);
                                btnStr.append(tmp & 0x1 ?  "1" : "0");
                                ++btnCnt;

                                if (btnCnt == 8) {
                                    std::cout << "   Buttons " << std::setw(3) << std::right << btnStart << "-" << std::left << std::setw(3) << btnStart+btnCnt-1 << "   " << btnStr.c_str() << std::endl;
                                    btnCnt = 0;
                                    btnStr.clear();
                                    rows++;
                                }
                            } // everything else
                            else {
                                if (btnCnt) {std::cout << "   Buttons " << std::setw(3) << std::right << btnStart << "-" << std::left << std::setw(3) << btnStart+btnCnt-1 << "   " << btnStr.c_str() << std::endl;
                                    btnCnt = 0;
                                    btnStr.clear();
                                    rows++;
                                }

                                u_int64_t tmp = decoder.extractValue(input, dataVect, true);
                                if (decoder.usage_names_.count(input.usage)) rows++;
                            }
                        }
                    }
                }
            }

            // a short sleep prevents the cursor from visually jumping all over the place
            usleep(100000);
            if (!keepReading) break;
            if (rows > 0) {
                for (int i = 0; i < rows; ++i) {
                    std::cout << "\x1b[A";
                }
            }
        }
    }

    hid_close(device);

    hid_exit();
    return 0;
}
