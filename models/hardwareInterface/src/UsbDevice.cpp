#include "UsbDevice.hh"
#include "IOException.hh"

#include <errno.h>
#include <sstream>
#include <cstring>
#include <algorithm>

using namespace idf;

int UsbDevice::instanceCount = 0;

std::vector<UsbDevice::DeviceTag> UsbDevice::openDevices;

UsbDevice::UsbDevice(int vendorID, int productID) :
    vendorId(vendorID) {
    productIds.push_back(productID);
    if (++instanceCount == 1) {
        if (hid_init() < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to initialize HID library.";
            throw IOException(oss.str());
        }
    }
}

UsbDevice::~UsbDevice() {
    if (--instanceCount == 0) {
        hid_exit();
    }
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
                        std::ostringstream oss;
                        oss << __FILE__ << ":" << __LINE__
                            << " Failed to open device: " << strerror(errno)
                            << " See the IDF README for troubleshooting.";
                        throw IOException(oss.str());
                    }
                }
            }
        }

        hid_free_enumeration(enumerationHead);

        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to find device.";
        throw IOException(oss.str());
    }
}

int UsbDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: device is not open.";
        throw IOException(oss.str());
    }

    int bytesRead = hid_read(hidDevice, buffer, length);

    if (bytesRead < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: " << strerror(errno);
        throw IOException(oss.str());
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
