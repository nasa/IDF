#include "UsbDevice.hh"

using namespace hardware;

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
    if (!this->mOpen) {
        for (std::vector<int>::iterator i = productIds.begin(); i != productIds.end(); ++i) {
            if ((hidDevice = hid_open(vendorId, *i, NULL))) {
                hid_set_nonblocking(hidDevice, 1);
                this->mOpen = true;
                return;
            }
        }
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
            << "Failed to find device.";
        throw IOException(oss.str().c_str());
    }
}

void UsbDevice::close() {
    if (this->mOpen) {
        hid_close(hidDevice);
        this->mOpen = false;
    }
}
