#include "CanDevice.hh"

using namespace hardware;

int CanDevice::instanceCount = 0;

CanDevice::CanDevice(int networkID, int baudRate) :
    mNetworkID(networkID),
    mBaudRate(baudRate) {
    if (++instanceCount == 1) {
        /*if (hid_init() < 0) {
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
                << "Failed to initialize HID library.";
            throw IOException(oss.str().c_str());
        }*/
    }
}

CanDevice::~CanDevice() {
    if (--instanceCount == 0) {
        //hid_exit();
    }
}

void CanDevice::open() {
    if (!this->mOpen) {
        /*for (std::vector<int>::iterator i = productIds.begin(); i != productIds.end(); ++i) {
            if ((hidDevice = hid_open(vendorId, *i, NULL))) {
                hid_set_nonblocking(hidDevice, 1);
                this->mOpen = true;
                return;
            }
        }*/
        std::ostringstream oss;
        oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
            << "Failed to find device.";
        throw IOException(oss.str().c_str());
    }
}

void CanDevice::close() {
    if (this->mOpen) {
        //hid_close(hidDevice);
        this->mOpen = false;
    }
}
