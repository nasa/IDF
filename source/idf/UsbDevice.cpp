#include "idf/UsbDevice.hh"
#include "idf/IOException.hh"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <sstream>

//deleteme
#include <iostream>

namespace idf {

int UsbDevice::instanceCount = 0;

std::map<UsbDevice*, std::string> UsbDevice::openDevices;

UsbDevice::UsbDevice(const std::string& id, unsigned length) :
    InputDevice(id),
    hidDevice(NULL),
    packetLength(length),
    serialNumber(),
    path() {
    if (++instanceCount == 1) {
        if (hid_init() < 0) {
            throw IOException("Failed to initialize HID library.");
        }
    }
    identifications["Ch Pdo Pedals"].push_back(Identification(0x068E, 0x00F2, 0));
    identifications["Daco THC DF0201"].push_back(Identification(0x1CFA, 0x0044, 0));
    identifications["Extreme 3D Pro"].push_back(Identification(0x046D, 0xC215, 0));
    identifications["Gravis"].push_back(Identification(0x0428, 0x4001, 0));
    identifications["Hagstrom KE-USB36"].push_back(Identification(0x03EB, 0x3650, 0));
    identifications["Hagstrom KE-USB36FS"].push_back(Identification(0x04B4, 0x3648, 0));
    identifications["Industrial Products"].push_back(Identification(0x068E, 0x002E, 0));
    identifications["Industrial Products 2"].push_back(Identification(0x068E, 0x0019, 0));
    identifications["Industrial Products 3"].push_back(Identification(0x068E, 0x0026, 0));
    identifications["Industrial Products 4"].push_back(Identification(0x068E, 0x0177, 0));
    identifications["Playstation 3 Controller"].push_back(Identification(0x054C, 0x0268, 0));
    identifications["Playstation 4 Controller"].push_back(Identification(0x054C, 0x05C4, 0));
    identifications["Playstation 4 Controller"].push_back(Identification(0x054C, 0x09CC, 3));
    identifications["Mad Catz"].push_back(Identification(0x0738, 0x1302, 0));
    identifications["Saitek"].push_back(Identification(0x06A3, 0x0763, 0));
    identifications["Saitek Pro Flight X52 Flight System"].push_back(Identification(0x06A3, 0x075C, 0));
    identifications["Saitek Pro Flight X-56 Rhino Stick"].push_back(Identification(0x0738, 0x2221, 0));
    identifications["Saitek Pro Flight X-56 Rhino Throttle"].push_back(Identification(0x0738, 0xA221, 0));
    identifications["Space Explorer"].push_back(Identification(0x046D, 0xC627, 0));
    identifications["Space Mouse"].push_back(Identification(0x046D, 0xC62B, 0));
    identifications["Space Mouse"].push_back(Identification(0x046D, 0xC635, 0));
    identifications["Space Navigator"].push_back(Identification(0x046D, 0xC626, 0));
    identifications["Space Navigator"].push_back(Identification(0x046D, 0xC628, 0));
    identifications["Space Navigator"].push_back(Identification(0x256F, 0xC635, 0));
    identifications["Teensyduino Joystick"].push_back(Identification(0x16C0, 0x0482, 3));
    identifications["Wing Man"].push_back(Identification(0x046D, 0xC212, 0));
    identifications["Xbox Controller"].push_back(Identification(0x045E, 0x028E, 0));
    identifications["Xbox One Wireless Controller"].push_back(Identification(0x045E, 0x02E0, -1));
    identifications["Xbox One S Controller [Bluetooth]"].push_back(Identification(0x045E, 0x02FD, -1));
}

UsbDevice::~UsbDevice() {
    close();
    if (--instanceCount == 0) {
        hid_exit();
    }
}

bool UsbDevice::isConnected() {
    bool connected = false;
    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo && !connected; deviceInfo = deviceInfo->next) {
        connected = deviceMatches(*deviceInfo);
    }
    hid_free_enumeration(enumerationHead);
    return connected;
}

void UsbDevice::setSerialNumber(const std::wstring& serial) {
    serialNumber = serial;
}

void UsbDevice::setPath(const std::string& newPath) {
    path = newPath;
}

void UsbDevice::addIdentification(const Identification& identification) {
    identifications[name].push_back(identification);
}

std::string UsbDevice::getPath() {
    std::map<UsbDevice*, std::string>::iterator element = openDevices.find(this);
    if (element != openDevices.end()) {
        return element->second;
    }
    return "";
}

bool UsbDevice::deviceMatches(const struct hid_device_info& deviceInfo) {
    if (!serialNumber.empty() && wcscmp(serialNumber.c_str(), deviceInfo.serial_number)) {
        return false;
    }
    if (!path.empty() && strcmp(resolvePath(path).c_str(), deviceInfo.path)) {
        return false;
    }
    for (std::vector<Identification>::iterator i = identifications[name].begin(); i != identifications[name].end(); ++i) {
        if (i->vendorId == deviceInfo.vendor_id && i->productId == deviceInfo.product_id && i->interfaceNumber == deviceInfo.interface_number) {
            return true;
        }
    }
    return false;
}

UsbDevice* UsbDevice::getInstanceAtPath(const std::string& targetPath) const {
    std::string resolvedPath = resolvePath(targetPath);
    for (std::map<UsbDevice*, std::string>::iterator i = openDevices.begin();
      i != openDevices.end(); ++i) {
        if (i->second == resolvedPath) {
            return i->first;
        }
    }
    return NULL;
}

void UsbDevice::open(const std::string& targetPath) {
    std::string resolvedPath = resolvePath(targetPath);
    std::ostringstream ss;
    ss << "Failed to open " << name << " at " << targetPath;
    if (resolvedPath != targetPath) {
        ss << " (which resolves to " << resolvedPath << ")";
    }
    ss << ": ";

    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        // if the path matches
        if (!strcmp(resolvedPath.c_str(), deviceInfo->path)) {

            // get the name of the device at this path
            std::string deviceAtPath = getDeviceName(Identification(*deviceInfo));

            // if it's empty, IDF doesn't know what it is
            if (deviceAtPath.empty()) {
                ss << "The combination of vendor, product, and interface IDs ("
                   << "0x" << std::hex << std::setw(4) << std::setfill('0') << deviceInfo->vendor_id << ", "
                   << "0x" << std::hex << std::setw(4) << std::setfill('0') << deviceInfo->product_id << ", "
                   << deviceInfo->interface_number
                   << ") for the device at this path is not known to IDF. You can try adding it "
                      "via UsbDevice::addIdentification, but if the encoding isn't identical, "
                      "you'll get garbage values.";
                hid_free_enumeration(enumerationHead);
                throw IOException(ss.str());
            }

            // if it doesn't match, it's a different device than what the user instaniated
            if (deviceAtPath != name) {
                ss << "The device at this path is a " << deviceAtPath;
                hid_free_enumeration(enumerationHead);
                throw IOException(ss.str());
            }

            // device name matches, check the serial number (if specified)
            if (!serialNumber.empty() && serialNumber.compare(deviceInfo->serial_number)) {
                ss << "Serial number mismatch";
                hid_free_enumeration(enumerationHead);
                throw IOException(ss.str());
            }

            // check that another instance isn't already open at this path
            UsbDevice* openInstance = getInstanceAtPath(resolvedPath);
            if (openInstance) {
                ss << "There is already a " << openInstance->name << " instance open at this path.";
                hid_free_enumeration(enumerationHead);
                throw IOException(ss.str());
            }

            // everything checks out, open the device
            hid_free_enumeration(enumerationHead);
            if (!(hidDevice = hid_open_path(resolvedPath.c_str()))) {
                ss << strerror(errno) << ". See the https://github.com/nasa/IDF/wiki for troubleshooting.";
                throw IOException(ss.str());
            }

            // open succeeded, update bookkeeping
            openDevices[this] = resolvedPath;
            hid_set_nonblocking(hidDevice, 1);
            return Manageable::open();
        }
    }

    // path not found
    hid_free_enumeration(enumerationHead);
    ss << "There is no device at this path.";
    throw IOException(ss.str());
}

void UsbDevice::open() {
    if (mOpen) {
        return;
    }

    if (!path.empty()) {
        return open(path);
    }

    struct hid_device_info *enumerationHead = hid_enumerate(0, 0);
    for (struct hid_device_info *deviceInfo = enumerationHead; deviceInfo; deviceInfo = deviceInfo->next) {
        if (deviceMatches(*deviceInfo) && !getInstanceAtPath(deviceInfo->path)) {
            const std::string devicePath = deviceInfo->path;
            hid_free_enumeration(enumerationHead);
            return open(devicePath);
        }
    }

    hid_free_enumeration(enumerationHead);
    std::ostringstream ss;
    ss << "Failed to find an available " << name;
    if (!serialNumber.empty()) {
        ss << " with the specified serial number";
    }
    ss << ". See https://github.com/nasa/IDF/wiki/HID-Scanner "
          "for a way to list information about connected devices.";

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
        openDevices.erase(this);
        hid_close(hidDevice);
        Manageable::close();
    }
}

std::string UsbDevice::resolvePath(const std::string& unresolvedPath) const {
    #ifdef __APPLE__
        return unresolvedPath;
    #else
        char resolvedPath[PATH_MAX];
        if (!realpath(unresolvedPath.c_str(), resolvedPath)) {
            throw IOException("Failed to resolve " + unresolvedPath + " for " + name + ": " + strerror(errno));
        }
        return resolvedPath;
    #endif
}

std::string UsbDevice::getDeviceName(const Identification& id) {
    for (std::map<std::string, std::vector<Identification> >::iterator i = identifications.begin();
         i != identifications.end(); ++i) {
        if (std::find(i->second.begin(), i->second.end(), id) != i->second.end()) {
            return i->first;
        }
    }
    return "";
}

}
