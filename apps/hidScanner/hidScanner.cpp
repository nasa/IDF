#include <algorithm>
#include <cstring>
#include <cwchar>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include "hidapi/hidapi/hidapi.h"

static volatile bool keepReading = true;

static unsigned getBit(unsigned char bit, unsigned value) {
    return (value >> bit) & 1;
}

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

    selection = -1;
    int numBytes = 64;

    switch (deviceInfo->vendor_id) {

        // Logitech
        case 0x046D:
            switch (deviceInfo->product_id) {
                /**
                 * 3Dconnexion devices return tranlsational, rotational, and button data in
                 * seperate messages. Button data is only returned when a button changes
                 * state, but translation and rotation data are both returned whenever
                 * either one changes state, making it very difficult to tell which bytes
                 * are changing as alternate messages scroll down the screen. Thus, for
                 * these devices, we ask the user to choose which type they wish to view.
                 */
                case 0xC626:
                case 0xC627:
                case 0xC628:
                case 0xC62B:
                    numBytes = 8;
                    printf("\nButton data will be shown when a button changes state.\n");
                    printf("Translational and rotational data are both sent when either\n");
                    printf("one changes, resulting in alternating messages which are\n");
                    printf("difficult to follow on-screen. Thus, this program only shows\n");
                    printf("one set at a time. Which set of data would you like to view?\n\n");
                    printf("1: translational\n");
                    printf("2: rotational\n\n");

                    while (selection < 1 || selection > 2) {
                        char buffer[1024];
                        printf("Select an option: ");
                        fgets(buffer, sizeof(buffer), stdin);
                        sscanf(buffer, "%d", &selection);
                    }
                    break;
            }
            break;

        // SONY
        case 0x054C:
            switch (deviceInfo->product_id) {

                // DualShock3
                case 0x0268:
                    numBytes = 49;
                    break;

                // DualShock4
                case 0x05C4:
                    numBytes = 64;
                    break;
            }
            break;

        // Industrial Products
        case 0x068E:
            numBytes = 12;
            break;

    }

    hid_free_enumeration(enumerationHead);

    hid_set_nonblocking(device, 1);

    unsigned char data[numBytes];

    while (keepReading) {
        int bytesRead = hid_read(device, data, sizeof(data));
        if (bytesRead < 0) {
            perror("Error reading from device");
            if (errno == EINTR) keepReading = false;
            else return -1;
        }
        else if (bytesRead > 0) {
            if (selection == -1 || data[0] == selection || data[0] == 3) {
                printf("\x1b[39;49mRead %d bytes:", bytesRead);
                int i;
                for (i = 0; i < bytesRead; ++i) {
                    printf("  ");
                    printf("\033[0;3%dm", i % 7 + 1);
                    int j = 7;
                    while(j > 3) {
                        printf("%u", getBit(j--, data[i]));
                    }
                    printf(" ");
                    while (j >= 0) {
                        printf("%u", getBit(j--, data[i]));
                    }
                }
                printf("\n");
            }
        }
    }

    unsigned char report[HID_API_MAX_REPORT_DESCRIPTOR_SIZE];
    int report_size = hid_get_report_descriptor(device, report, sizeof(report));

    if (report_size < 0) {
        perror("Error reading HID Report Descriptor from device");
        return -1;
    }

    printf("\x1b[39;49m\nHID Report Descriptor (%d bytes):\n   ", report_size);
    for(int i=0; i < report_size; ++i) {
        printf("%02X ", report[i]);
        if (i % 16 == 15) printf("\n   ");
        else if (i % 8 == 7) printf(" ");
    }
    printf("\n");

    hid_exit();
    return 0;
}
