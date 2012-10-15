#include "UsbWingMan.hh"

using namespace idf;

UsbWingMan::UsbWingMan(int vendorID, int productID) :
    UsbDevice(vendorID, productID) {}

void UsbWingMan::update() {
    UsbDevice::update();

    int bytesRead;
    int totalBytesRead = 0;
    int index = 0;
    unsigned char buffer[6];

    /**
     * Read all data on the line, account for partial packets, and discard
     * everything but the last packet. This ensures that this class reflects
     * the most recent data from the device, regardless of potential mismatches
     * between the rate at which this function is called and the rate at which
     * the device is sending data.
     */
    do {
        bytesRead = hid_read(hidDevice, buffer + index, sizeof(buffer) - index);

        if (bytesRead > 0) {
            totalBytesRead += bytesRead;
            index = totalBytesRead % sizeof(buffer);
        }
        else if (bytesRead < 0) {
            mOpen = false;
            std::ostringstream oss;
            oss << __FILE__ << ":" << __LINE__ << " (" << __FUNCTION__ << ") "
                << "Error while updating.";
            throw IOException(oss.str().c_str());
        }
    } while (bytesRead > 0 || index);

    // At this point, either no data was available, or we have a full buffer.
    if (totalBytesRead) {
            leftRightPivot.setValue(((unsigned)buffer[1] & 3) << 8 | buffer[0]);
            forwardBackwardPivot.setValue(((unsigned)buffer[2] & 0xF) << 6 | buffer[1] >> 2);
            twist.setValue(buffer[3]);

            trigger.setValue(buffer[4] & 1);
            button2.setValue(buffer[4] >> 1 & 1);
            button3.setValue(buffer[4] >> 2 & 1);
            button4.setValue(buffer[4] >> 3 & 1);
            button5.setValue(buffer[4] >> 4 & 1);
            button6.setValue(buffer[4] >> 5 & 1);
            button7.setValue(buffer[4] >> 6 & 1);

            unsigned int hat = buffer[2] >> 4;

            hatNorth.setValue(hat == 0);
            hatNorthEast.setValue(hat == 1);
            hatEast.setValue(hat == 2);
            hatSouthEast.setValue(hat == 3);
            hatSouth.setValue(hat == 4);
            hatSouthWest.setValue(hat == 5);
            hatWest.setValue(hat == 6);
            hatNorthWest.setValue(hat == 7);

            slider.setValue(buffer[5]);
    }
}

void UsbWingMan::printState() {
    std::cout << "F/B: " << forwardBackwardPivot.toString()
              << " L/R: " << leftRightPivot.toString()
              << " Twist: " << twist.toString()
              << " trigger: " << trigger.toString()
              << " b2: " << button2.toString()
              << " b3: " << button3.toString()
              << " b4: " << button4.toString()
              << " b5: " << button5.toString()
              << " b6: " << button6.toString()
              << " b7: " << button7.toString()
              << " N: " << hatNorth.toString()
              << " NE: " << hatNorthEast.toString()
              << " E: " << hatEast.toString()
              << " SE: " << hatSouthEast.toString()
              << " S: " << hatSouth.toString()
              << " SW: " << hatSouthWest.toString()
              << " W: " << hatWest.toString()
              << " NW: " << hatNorthWest.toString()
              << " slider: " << slider.toString()
              << std::endl;
}
