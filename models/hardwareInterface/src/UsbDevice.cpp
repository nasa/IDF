#include "UsbDevice.hh"
#include "IOException.hh"

#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <cstring>

using namespace idf;

int UsbDevice::instanceCount = 0;

UsbDevice::UsbDevice(int vendorID, int productID) :
    vendorId(vendorID) {
    productIds.push_back(productID);
    if (++instanceCount == 1) {
        if (hid_init() < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__
                << " Failed to initialize HID library.";
            throw IOException(oss.str().c_str());
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
            if (deviceInfo->vendor_id == vendorId) {
                for (std::vector<int>::iterator i = productIds.begin(); i != productIds.end(); ++i) {
                    if (deviceInfo->product_id == *i) {
                        if ((hidDevice = hid_open_path(deviceInfo->path))) {
                            hid_free_enumeration(enumerationHead);
                            hid_set_nonblocking(hidDevice, 1);
                            mOpen = true;
                            return;
                        }
                        else {
                            hid_free_enumeration(enumerationHead);
                            std::ostringstream oss;
                            oss << __FILE__ << ":" << __LINE__
                                << " Failed to open device: " << strerror(errno);
                            throw IOException(oss.str().c_str());
                        }
                    }
                }
            }
        }

        hid_free_enumeration(enumerationHead);

        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Failed to find device.";
        throw IOException(oss.str().c_str());
    }
}

int UsbDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: device is not open.";
        throw IOException(oss.str().c_str());
    }

    int bytesRead = hid_read(hidDevice, buffer, length);

    if (bytesRead < 0) {
        close();
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__
            << " Error while reading: " << strerror(errno);
        throw IOException(oss.str().c_str());
    }

    return bytesRead;
}

void UsbDevice::close() {
    if (mOpen) {
        hid_close(hidDevice);
        mOpen = false;
    }
}
