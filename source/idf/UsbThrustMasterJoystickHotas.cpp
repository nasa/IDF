#include "idf/UsbThrustMasterJoystickHotas.hh"

namespace idf {

UsbThrustMasterJoystickHotas::UsbThrustMasterJoystickHotas() :
    UsbDevice("ThrustMaster Joystick - HOTAS", 12) {}


UsbThrustMasterJoystickHotas::UsbThrustMasterJoystickHotas(const std::string& id, unsigned length) :
    UsbDevice(id, length) {}

void UsbThrustMasterJoystickHotas::decode(const std::vector<unsigned char>& data) {
    leftRightPivot.setValue( ((unsigned)data[5] & 0xFF) << 8 | data[4] );
    forwardBackwardPivot.setValue( ((unsigned)data[7] & 0xFF) << 8 | data[6] );

    /* The other buttons are not read in due to lacking an unmodified unit with intact buttons*/
    // trigger.setValue( data[8] & 0x1);
    // triggerStage2.setValue( data[9] >> 6 & 0x1);
    // button2.setValue( data[8] >> 2 & 0x1);
    // button3.setValue( data[8] >> 3 & 0x1);
    // button4.setValue( data[8] >> 4 & 0x1);
    // button5.setValue( data[8] >> 6 & 0x1);
    // button19.setValue( data[8] >> 7 & 0x1);

    // char hat1 = (data[10] << 1 & 0xE) | (data[9] >> 7 & 0x1);
    // char hat2 = (data[12] >> 4 & 0xF);
    // char hat3 = (data[10] >> 3 & 0xF);
    // char hat4 = (data[10] >> 3 & 0xF);

    // hat1UpDownPivot.setValue(   hat1 & 0x1 ? 1 : hat1 & 0x4 ? -1 : 0 );
    // hat1LeftRightPivot.setValue(hat1 & 0x8 ? 1 : hat1 & 0x2 ? -1 : 0 );
    // hat1North.setValue(     hat1 == 1 );
    // hat1NorthEast.setValue( hat1 == 3 );
    // hat1East.setValue(      hat1 == 2 );
    // hat1SouthEast.setValue( hat1 == 6 );
    // hat1South.setValue(     hat1 == 4 );
    // hat1SouthWest.setValue( hat1 == 12 );
    // hat1West.setValue(      hat1 == 8 );
    // hat1NorthWest.setValue( hat1 == 9 );

    // hat2UpDownPivot.setValue( (hat2 == 1 || hat2 == 2 || hat2 == 8) ? 1 : (hat2 >=4 && hat2 <=6) ? -1 : 0 );
    // hat2LeftRightPivot.setValue(hat2 >=6 && hat3 <= 8 ? 1 : hat2 >=2 && hat2 <=4 ? -1 : 0 );
    // hat2North.setValue(     hat2 == 1 );
    // hat2NorthEast.setValue( hat2 == 2 );
    // hat2East.setValue(      hat2 == 3 );
    // hat2SouthEast.setValue( hat2 == 4 );
    // hat2South.setValue(     hat2 == 5 );
    // hat2SouthWest.setValue( hat2 == 6 );
    // hat2West.setValue(      hat2 == 7 );
    // hat2NorthWest.setValue( hat2 == 8 );

    // hat3UpDownPivot.setValue(   hat3 & 0x1 ? 1 : hat3 & 0x4 ? -1 : 0 );
    // hat3LeftRightPivot.setValue(hat3 & 0x8 ? 1 : hat3 & 0x2 ? -1 : 0 );
    // hat3North.setValue(     hat3 == 1 );
    // hat3NorthEast.setValue( hat3 == 3 );
    // hat3East.setValue(      hat3 == 2 );
    // hat3SouthEast.setValue( hat3 == 6 );
    // hat3South.setValue(     hat3 == 4 );
    // hat3SouthWest.setValue( hat3 == 12 );
    // hat3West.setValue(      hat3 == 8 );
    // hat3NorthWest.setValue( hat3 == 9 );

    // hat4UpDownPivot.setValue(   hat4 & 0x1 ? 1 : hat4 & 0x4 ? -1 : 0 );
    // hat4LeftRightPivot.setValue(hat4 & 0x8 ? 1 : hat4 & 0x2 ? -1 : 0 );
    // hat4North.setValue(     hat4 == 1 );
    // hat4East.setValue(      hat4 == 2 );
    // hat4South.setValue(     hat4 == 4 );
    // hat4West.setValue(      hat4 == 8 );
}

}
