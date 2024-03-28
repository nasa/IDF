#include <algorithm>
#include <cstring>
#include <cwchar>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "hidapi/hidapi/hidapi.h"

namespace {
    int server;
    struct sockaddr_in serverAddr;

    int client;
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    bool connected = false;

    struct hid_device_info * deviceInfo;
    bool tcp = true;
}

static unsigned getBit(unsigned char bit, unsigned value) {
    return (value >> bit) & 1;
}

void usage(){
    printf("\nUsage:\n\tsocketter <port> [-udp] [-d <vendorid> <productid>]\n\n");
}

unsigned short validatePort(char* port_in) {
    int port = 0;
    try{
        port = std::stoi(port_in);
    } catch (std::invalid_argument const& ex) {
        fprintf(stderr, "\ninvalid input '%s'\n", port_in);
        usage();
        std::exit(-1);
    } catch (std::out_of_range const& ex) {
        fprintf(stderr, "\nport out of range '%s'\n", port_in);
        std::exit(-1);
    }
    if (port > 65535) {
        fprintf(stderr, "\nport out of valid range 1024-65535\n\n");
        std::exit(-1);
    } else if (port == 0) {
        fprintf(stderr, "\nWARNING: port 0 will bind a random port\n");
    }
    return (unsigned short) port;
}

unsigned short validateId(char* id_in) {
    int id = -1;
    try {
        id = std::stoi(id_in, nullptr, 16);
    } catch (std::invalid_argument const& ex) {
        fprintf(stderr, "\ninvalid input '%s'\n", id_in);
        usage();
        std::exit(-1);
    } catch (std::out_of_range const& ex) {
        fprintf(stderr, "\nport out of range '%s'\n", id_in);
        std::exit(-1);
    }
    return id;
}

void acceptClient() {
    printf("Listening for%s client on port %d\n", tcp ? "" : " UDP", ntohs(serverAddr.sin_port));
    if (tcp) {
        
        while((client = accept(server, (struct sockaddr*)&clientAddr, &clientAddrLen)) < 0){
            connected = false;
            perror("Failed to accept client");
            std::exit(-1);
        }
    } else {

        unsigned char data[1024] = {0};
        while(recvfrom(server, data, sizeof(data), MSG_WAITALL, (struct sockaddr*)&clientAddr, &clientAddrLen) < 0) {
            connected = false;
            perror("Failed to accept client");
            std::exit(-1);
        }
    }
    connected = true;
    printf("Client connected %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    printf("Serving device: 0x%04X,0x%04X\n", deviceInfo->vendor_id, deviceInfo->product_id);
}

int main(int argc, char **args) {
    if (argc <= 1) {
        usage();
        return 0;
    }

    // process arguments
    unsigned short port = validatePort(args[1]);

    int vendId = -1;
    int prodId = -1;
    int sockType = SOCK_STREAM;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(args[i],"-d") == 0) {
            if (argc < i+2) {
                fprintf(stderr, "flag -d requires 2 parameters: <vendor_id> <product_id>\n");
                usage();
                std::exit(-1);
            }
            vendId = validateId(args[i+1]);
            prodId = validateId(args[i+2]);
        } else if (strcmp(args[i], "-udp") == 0) {
            printf("Setting UDP\n");
            tcp = false;
            sockType = SOCK_DGRAM;
        }
    }

    // create socket
    server = socket(AF_INET, sockType, 0);
    if (errno > 0) {
        perror("failed to create socket");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // init HID library and connect device
    int result = hid_init();
    if (result < 0) {
        printf("Failed to initialize HID library.\n");
        return -1;
    }

    struct hid_device_info* enumerationHead = hid_enumerate(0, 0);
    deviceInfo = 0;

    int selection = -1;

    if (vendId != -1 && prodId != -1) {
        int found = false;
        for (deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
            selection++;
            if (deviceInfo->vendor_id == vendId && deviceInfo->product_id == prodId) {
                found = true;
                printf("Confirmed device: 0x%04X,0x%04X\n", deviceInfo->vendor_id, deviceInfo->product_id);
                break;
            }
        }
        if (!found) {
            printf("Device not found: 0x%04X,0x%04X\n", vendId, prodId);
        }
    }

    if (!deviceInfo) {

        size_t serialLength = std::wcslen(L"Serial #");
        size_t vendorLength = std::wcslen(L"Vendor");
        size_t pathLength   = std::strlen("Path");
        for(deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
            serialLength = std::max(serialLength, wcslen(deviceInfo->serial_number));
            vendorLength = std::max(vendorLength, wcslen(deviceInfo->manufacturer_string));
            pathLength   = std::max(pathLength, strlen(deviceInfo->path));
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

        selection = -1;
        printf("\n");

        while (selection < 0 || selection > count -1) {
            char buffer[1024];
            printf("Select a device to listen to: ");
            fgets(buffer, sizeof(buffer), stdin);
            sscanf(buffer, "%d", &selection);
        }

        deviceInfo = enumerationHead;
        for (count = 0; count < selection; ++count) {
            deviceInfo = deviceInfo->next;
        }
    }

    hid_device* device = hid_open_path(deviceInfo->path);
    if (!device) {
        perror("Failed to open device");
        close(server);
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

    unsigned char data[numBytes] = { 0 };

    bind(server, (struct sockaddr*)& serverAddr, sizeof(serverAddr));
    if (errno > 0) {
        // fprintf(stderr, "Could not bind port %d: %s\n", port, strerror(errno));
        perror("Cound not bind port");
        return -1;
    }

    if(tcp) {
        listen(server, 5);
        if (errno > 0) {
            perror("failed to listen for clients");
            return -1;
        }

        socklen_t boundLen = sizeof(serverAddr);
        getsockname(server, (struct sockaddr *)&serverAddr, &boundLen);
    }

    acceptClient();

    char sendBuffer[128] = {0};
    size_t buffLen = 0;

    // read once to get actual number of bytes to read.
    int bytesRead = hid_read(device, data, sizeof(data));
    if (bytesRead < 0) {
        perror("Error reading from device");
        return -1;
    }

    int sent = 0;

    while (1) {
        if(!connected) {
            acceptClient();
        }

        bytesRead = hid_read(device, data, sizeof(data));
        if (bytesRead < 0) {
            perror("Error reading from device");
            return -1;
        }
        else if (bytesRead > 0) {
            if (selection == -1 || data[0] == selection || data[0] == 3) {
                sent = tcp ? send(client, data, bytesRead, MSG_NOSIGNAL)
                           : sendto(server, data, bytesRead, MSG_NOSIGNAL, (struct sockaddr*)&clientAddr, clientAddrLen);
                if(sent < 0) {
                    perror("Error sending to client");
                    close(client);
                    connected = false;
                }
            }
        }
    }
    close(client);
    close(server);
    hid_exit();
    return 0;
}