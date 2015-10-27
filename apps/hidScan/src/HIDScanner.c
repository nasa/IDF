#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "hidapi/hidapi.h"

static unsigned getBit(unsigned char bit, unsigned value) {
    return (value >> bit) & 1;
}

int main(int argc, char **args) {

    int result = hid_init();
    if (result < 0) {
        printf("Failed to initialize HID library.\n");
        return -1;
    }

    struct hid_device_info* enumerationHead = hid_enumerate(0, 0);
    int count = 0;

    printf("\nNOTE: If running as non-root, you must have udev rules in place allowing access to usb devices.\n\n");
    printf("Index  Vendor ID  Product ID  Vendor          Product\n");

    struct hid_device_info * deviceInfo;
    for (deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next, ++count) {
        printf("%-6d 0x%04hX     0x%04hX      %-15ls %ls\n", count,
          deviceInfo->vendor_id, deviceInfo->product_id,
          deviceInfo->manufacturer_string ? deviceInfo->manufacturer_string : L"null",
          deviceInfo->product_string ? deviceInfo->product_string : L"null");
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

    int numBytes;
    switch (deviceInfo->vendor_id) {
        /**
         * 3Dconnexion devices return tranlsational, rotational, and button data in
         * seperate messages. Button data is only returned when a button changes
         * state, but translation and rotation data are both returned whenever
         * either one changes state, making it very difficult to tell which bytes
         * are changing as alternate messages scroll down the screen. Thus, for
         * these devices, we ask the user to choose which type they wish to view.
         */
        case 0x046D:
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

        default:
            numBytes = 8;
            break;

    }

    hid_free_enumeration(enumerationHead);

    hid_set_nonblocking(device, 1);

    unsigned char data[numBytes];

    /**
     * Rumble Pack Bytes
     * report number: always 1
     * |     duration of weak (right) rumble, units = 20 ms, 0xff = infinity
     * |     |     magnitude of weak (right) rumble
     * |     |     |     duration of strong (left) rumble, units = 20 ms, 0xff = infinity
     * |     |     |     |     magnitude of strong (left) rumble
     * |     |     |     |     |
     * 0x01, 0xfe, 0xff, 0xfe, 0xff
     *
     * LED Bytes - LEDs start their cycle in the off stage
     * the total time this command is applied, after which the LED turns off, units = 20 ms, 0xff = infinity
     * |     integer part of the cycle period
     * |     |     fractional part of the cycle period in increments of 1 / 255. Thus, you can specify a cycle
     * |     |     | period of 256 by entering 255 for both the integer and fractional parts
     * |     |     |     multiplied by the cycle period to determine how long the LED is off per cycle
     * |     |     |     |     multiplied by the cycle period to determine how long the LED is on per cycle
     * |     |     |     |     |
     * 0xff, 0x27, 0x10, 0x32, 0x32
     *
     * Command Packet Bytes
     *   0 - 4 = rumble pack parameters
     *   5 - 8 = unused
     *       9 = bitwise OR of LEDs to be powered. LED1 = 2, LED2 = 4, LED3 = 8, LED4 = 16
     * 10 - 14 = LED4 parameters
     * 15 - 19 = LED3 parameters
     * 20 - 24 = LED2 parameters
     * 25 - 29 = LED1 parameters
     *
     * Per LED, a command different from it's current state takes effect immediately. Commands that do not
     * change the state are ignored, and will not "reset" the LED's cycle. Cycles start in the off portion.
     */

    /*unsigned char command[] = {
        1, 254, 255, 254, 255,
        0, 0x00, 0x00, 0x00, 0x1E,
        255, 32, 0, 50, 50,
        255, 64, 0, 50, 50,
        255, 128, 0, 50, 50,
        255, 255, 255, 50, 50
    };

    unsigned char usbWakeup[] = {0xf2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char bluetoothWakeup[] = {0xf4,  0x42, 0x03, 0x00, 0x00};

    int length = sizeof(usbWakeup);
    printf("Requesting feature report.\n");
    if (hid_get_feature_report(device, usbWakeup, length) < length) {
        #ifdef __linux__
            perror("Failed to get feature report");
            printf("errno = %d\n", errno);
        #else
            printf("Failed to get feaature report.\n");
        #endif
        return -1;
    }

    int i;
    printf("Feature report returned: ");
    for (i = 0; i < sizeof(usbWakeup); ++i) {
        printf("%x ", (int)usbWakeup[i]);
    }
    printf("\n");

    printf("Sending feature report.\n");
    length = sizeof(bluetoothWakeup);
    if (hid_send_feature_report(device, bluetoothWakeup, length) < length) {
        #ifdef __linux__
            perror("Failed to send wakeup command");
            printf("errno = %d\n", errno);
        #else
            printf("Failed to send wakeup command.\n");
        #endif
        return -1;
    }*/

    /*printf("Writing command.\n");
    if (hid_write(device, command, sizeof(command)) < sizeof(command)) {
        #ifdef __linux__
            perror("Failed to send command");
            printf("errno = %d\n", errno);
        #else
            printf("Failed to send command.\n");
        #endif
        return -1;
    }*/

    while (1) {
        int bytesRead = hid_read(device, data, sizeof(data));
        if (bytesRead < 0) {
            perror("Error reading from device");
            return -1;
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

    hid_exit();
    return 0;
}
