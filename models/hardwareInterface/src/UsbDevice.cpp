#include "hardwareInterface/include/UsbDevice.hh"
#include "hardwareInterface/include/IOException.hh"

#include <errno.h>
#include <sstream>
#include <cstring>
#include <algorithm>

namespace idf {

int UsbDevice::instanceCount = 0;

std::vector<UsbDevice::DeviceTag> UsbDevice::openDevices;

UsbDevice::UsbDevice(const std::string& id, int vendorID, int productID, unsigned length) :
    InputDevice(id),
    vendorId(vendorID),
    packetLength(length) {
    productIds.push_back(productID);
    if (++instanceCount == 1) {
        if (hid_init() < 0) {
            throw IOException("Failed to initialize HID library.");
        }
    }
}

UsbDevice::~UsbDevice() {
    if (--instanceCount == 0) {
        hid_exit();
    }
}

bool UsbDevice::isConnected() {
    bool result = false;
    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        if (deviceInfo->vendor_id == vendorId) {
            if (std::find(productIds.begin(), productIds.end(), deviceInfo->product_id) != productIds.end()) {
                result = true;
                break;
            }
        }
    }
    hid_free_enumeration(enumerationHead);
    return result;
}

void UsbDevice::open() {
    if (!mOpen) {
        struct hid_device_info *enumerationHead = hid_enumerate(0, 0);

        for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {

            std::string path(deviceInfo->path);
            bool pathAlreadyOpen = false;
            for (std::vector<DeviceTag>::iterator i = openDevices.begin(); i < openDevices.end(); ++i) {
                if (i->path == path) {
                    pathAlreadyOpen = true;
                    break;
                }
            }
            if (pathAlreadyOpen) {
                continue;
            }

            if (deviceInfo->vendor_id == vendorId) {
                if (std::find(productIds.begin(), productIds.end(), deviceInfo->product_id) != productIds.end()) {
                    if ((hidDevice = hid_open_path(deviceInfo->path))) {
                        openDevices.push_back(DeviceTag(hidDevice, path));
                        hid_free_enumeration(enumerationHead);
                        hid_set_nonblocking(hidDevice, 1);
                        mOpen = true;
                        return;
                    }
                    else {
                        hid_free_enumeration(enumerationHead);
                        throw IOException("Failed to open " + name + ": " + strerror(errno) +
                          ". See the IDF wiki for troubleshooting: https://github.com/nasa/IDF/wiki");
                    }
                }
            }
        }

        hid_free_enumeration(enumerationHead);

        throw IOException("Failed to find " + name + ".");
    }
}

std::vector<std::vector<unsigned char> > UsbDevice::read() {
    std::vector<std::vector<unsigned char> > results;
    std::vector<unsigned char> buffer(packetLength);

    while (read(&buffer[0], buffer.size())) {
        results.push_back(buffer);
    }

    return results;
}


unsigned UsbDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        open();
    }

    int bytesRead = hid_read(hidDevice, buffer, length);
    if (bytesRead < 0) {
        close();
        throw IOException("Error while reading " + name + ": " + strerror(errno));
    }
    return bytesRead;
}

void UsbDevice::close() {
    if (mOpen) {
        for (std::vector<DeviceTag>::iterator i = openDevices.begin(); i < openDevices.end(); ++i) {
            if (i->handle == hidDevice) {
                openDevices.erase(i);
                break;
            }
        }
        hid_close(hidDevice);
        mOpen = false;
    }
}

}
