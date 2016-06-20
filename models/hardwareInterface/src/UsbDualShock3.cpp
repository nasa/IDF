#include "hardwareInterface/include/UsbDualShock3.hh"
#include "hardwareInterface/include/IOException.hh"

#include <stdio.h>
#include <errno.h>
#include <sstream>
#include <cstring>

// TODO: add an option to build with libusb

//#ifdef __linux__
//#include <libusb.h>

/**
 * This is required to access fields within struct hid_device in the
 * sendCommand function. hid_device_ is defined in hid.c, which cannot be
 * included here, so we have to replicate some of its definition. It's an ugly
 * hack, but it's the best I have for now.
 */
/*struct hid_device_ {
    libusb_device_handle *device_handle;
    int a, b, c, interface;
};
#endif*/

namespace idf {

UsbDualShock3::UsbDualShock3(int vendorID, int productID) :
    UsbDualShock("Playstation 3 Controller", vendorID, productID, 49) {}

void UsbDualShock3::decode(const std::vector<unsigned char>& data) {
    selectButton.setValue(data[2] & 1);
    leftAnalogIn.setValue(data[2] >> 1 & 1);
    rightAnalogIn.setValue(data[2] >> 2 & 1);
    startButton.setValue(data[2] >> 3 & 1);

    psButton.setValue(data[4] & 1);

    leftAnalogLeftRightPivot.setValue(data[6]);
    leftAnalogUpDownPivot.setValue(data[7]);
    rightAnalogLeftRightPivot.setValue(data[8]);
    rightAnalogUpDownPivot.setValue(data[9]);

    directionalPadUp.setValue(data[14]);
    directionalPadRight.setValue(data[15]);
    directionalPadDown.setValue(data[16]);
    directionalPadLeft.setValue(data[17]);

    leftTrigger.setValue(data[18]);
    rightTrigger.setValue(data[19]);
    leftBumper.setValue(data[20]);
    rightBumper.setValue(data[21]);

    triangleButton.setValue(data[22]);
    circleButton.setValue(data[23]);
    xButton.setValue(data[24]);
    squareButton.setValue(data[25]);
}

void UsbDualShock3::sendCommand() {
    if (!mOpen) {
        UsbDevice::open();
    }

//#ifdef __linux__
    /**
     * This devices incorrectly requires that commands be sent over the control
     * endpoint, so we have to call libusb directly rather than use hidapi,
     * which would use the interrupt out endpoint.
     */
    //int result = libusb_control_transfer(hidDevice->device_handle,
    //  LIBUSB_REQUEST_TYPE_CLASS | LIBUSB_RECIPIENT_INTERFACE | LIBUSB_ENDPOINT_OUT,
    //  0x09 /* HID set report */, (2 /* HID output */ << 8) | command[0],
    //  hidDevice->interface, command, sizeof(command), 1000);

    /*if (result < 0) {
        std::ostringstream stream;
        stream << name << ": Transfer failed with LIBUSB_ERROR code " << result;
        throw IOException(stream.str());
    }
#endif*/
}

}
