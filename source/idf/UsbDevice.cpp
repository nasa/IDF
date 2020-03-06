#include "idf/UsbDevice.hh"
#include "idf/IOException.hh"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <sstream>

namespace idf {

int UsbDevice::instanceCount = 0;

std::vector<UsbDevice::DeviceTag> UsbDevice::openDevices;

UsbDevice::UsbDevice(const std::string& id, int vendorID, int productID, unsigned length) :
    InputDevice(id),
    vendorId(vendorID),
    hidDevice(NULL),
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
        if (deviceInfo->vendor_id == vendorId &&
          std::find(productIds.begin(), productIds.end(), deviceInfo->product_id) != productIds.end()) {
            if (devicePath.empty()) {
                result = true;
            }
            else {
                result = devicePath == deviceInfo->path;
            }
        }
    }
    hid_free_enumeration(enumerationHead);
    return result;
}

void UsbDevice::setSerialNumber(const std::wstring& serial) {
    serialNumber = serial;
}

void UsbDevice::setPath(const std::string& path) {
    devicePath = path;
}

bool UsbDevice::deviceMatches(const struct hid_device_info& deviceInfo) const {
    bool result = deviceInfo.vendor_id == vendorId &&
      std::find(productIds.begin(), productIds.end(), deviceInfo.product_id) != productIds.end();
    if (!serialNumber.empty()) {
        result &= !serialNumber.compare(deviceInfo.serial_number);
    }
    return result;
}

bool UsbDevice::isPathOpen(const std::string& path) const {
    for (std::vector<DeviceTag>::iterator i = openDevices.begin(); i < openDevices.end(); ++i) {
        if (i->path == path) {
            return true;
        }
    }
    return false;
}

void UsbDevice::open(const std::string& path) {
    #ifdef __APPLE__
        const char *resolvedPath = path.c_str();
    #else
        char resolvedPath[PATH_MAX];
        if (!realpath(path.c_str(), resolvedPath)) {
            throw IOException("Failed to open " + name + ": Failed to resolve " + path + ": " + strerror(errno));
        }
    #endif

    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        if (!strcmp(resolvedPath, deviceInfo->path)) {
            if (!deviceMatches(*deviceInfo)) {
                hid_free_enumeration(enumerationHead);
                std::ostringstream ss;
                ss << "Failed to open " + name + ": The device at " + path + " (" + resolvedPath + ") is not a " + name;
                if (!serialNumber.empty()) {
                    ss << " or does not match the required serial number";
                }
                throw IOException(ss.str());
            }

            hid_free_enumeration(enumerationHead);
            if (isPathOpen(resolvedPath)) {
                throw IOException("Failed to open " + name + ": There is already a device open at " + path + " (" + resolvedPath + ")");
            }

            if (!(hidDevice = hid_open_path(resolvedPath))) {
                throw IOException("Failed to open " + name + " at " + path + " (" + resolvedPath + "): " + strerror(errno) +
                  ". See the IDF wiki for troubleshooting: https://github.com/nasa/IDF/wiki");
            }

            openDevices.push_back(DeviceTag(hidDevice, resolvedPath));
            hid_set_nonblocking(hidDevice, 1);
            return Manageable::open();
        }
    }

    hid_free_enumeration(enumerationHead);
    throw IOException("Failed to open " + name + ": There is no device at " + path + " (" + resolvedPath + ")");
}

void UsbDevice::open() {
    if (mOpen) {
        return;
    }

    if (!devicePath.empty()) {
        return open(devicePath);
    }

    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        if (deviceMatches(*deviceInfo) && !isPathOpen(deviceInfo->path)) {
            const std::string path = deviceInfo->path;
            hid_free_enumeration(enumerationHead);
            return open(path);
        }
    }

    hid_free_enumeration(enumerationHead);
    std::ostringstream ss;
    ss << "Failed to find an available " << name;
    if (!serialNumber.empty()) {
        ss << " with the required serial number";
    }
    throw IOException(ss.str());
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
        Manageable::close();
    }
}

}
