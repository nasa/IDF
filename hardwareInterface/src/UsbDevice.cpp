#include "UsbDevice.hh"
#include <cstring>

using namespace idf;

int UsbDevice::instanceCount = 0;

UsbDevice::UsbDevice(int vendorID, int productID) :
    vendorId(vendorID) {
    productIds.push_back(productID);
    if (++instanceCount == 1) {
        if (hid_init() < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
                << "Failed to initialize HID library.";
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
        for (std::vector<int>::iterator i = productIds.begin(); i != productIds.end(); ++i) {
            if ((hidDevice = hid_open(vendorId, *i, NULL))) {
                hid_set_nonblocking(hidDevice, 1);
                mOpen = true;
                return;
            }
        }
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
            << "Failed to find device.";
        throw IOException(oss.str().c_str());
    }
}

int UsbDevice::read(unsigned char *buffer, size_t length) {
    if (!mOpen) {
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
            << "Error while reading: device is not open " << strerror(errno);
        throw IOException(oss.str().c_str());
    }

    int bytesRead = hid_read(hidDevice, buffer, length);

    if (bytesRead < 0) {
        mOpen = false;
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
            << "Error while reading: " << strerror(errno);
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
