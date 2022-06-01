cmake_minimum_required(VERSION 2.4.4)
project(IDF)

option(ENABLE_CAN_DEVICES "Enable CAN controlled input devices" OFF)

if(${ENABLE_CAN_DEVICES})
    set(SRC_IDF
        source/idf/CanDevice.cpp
        source/idf/CanIndustrialProducts.cpp
    )
endif(${ENABLE_CAN_DEVICES})

set(SRC_IDF
    ${SRC_IDF}
    source/idf/CameraController.cpp
    source/idf/ChProPedals.cpp
    source/idf/CompositeCameraController.cpp
    source/idf/CompositeFlightController.cpp
    source/idf/CompositeInput.cpp
    source/idf/CompositeRoboticsController.cpp
    source/idf/Controller.cpp
    source/idf/Deadbandable.cpp
    source/idf/Deadband.cpp
    source/idf/DualShock3.cpp
    source/idf/DualShock4.cpp
    source/idf/DualShock.cpp
    source/idf/Er7Orion.cpp
    source/idf/SerialEr7Orion.cpp
    source/idf/Extreme3dPro.cpp
    source/idf/FlightController.cpp
    source/idf/Gravis.cpp
    source/idf/HagstromKEUSB36.cpp
    source/idf/IndustrialProducts2.cpp
    source/idf/IndustrialProducts3.cpp
    source/idf/IndustrialProducts.cpp
    source/idf/Input.cpp
    source/idf/InputDevice.cpp
    source/idf/InputLayout.cpp
    source/idf/Keyboard.cpp
    source/idf/MadCatz.cpp
    source/idf/Manageable.cpp
    source/idf/MutualExclusionGroup.cpp
    source/idf/Output.cpp
    source/idf/RemoteCameraController.cpp
    source/idf/RemoteExtreme3dPro.cpp
    source/idf/RemoteFlightController.cpp
    source/idf/RemoteRoboticsController.cpp
    source/idf/RemoteSpaceNavigator.cpp
    source/idf/RoboticsController.cpp
    source/idf/Saitek.cpp
    source/idf/SerialDevice.cpp
    source/idf/SerialThrustMaster2.cpp
    source/idf/SerialThrustMasterBase.cpp
    source/idf/SerialThrustMaster.cpp
    source/idf/SingleCameraController.cpp
    source/idf/SingleFlightController.cpp
    source/idf/SingleInput.cpp
    source/idf/SingleRoboticsController.cpp
    source/idf/SpaceBase.cpp
    source/idf/SpaceExplorer.cpp
    source/idf/SpaceMouse.cpp
    source/idf/SpaceNavigator.cpp
    source/idf/ThrustMaster2.cpp
    source/idf/ThrustMasterBase.cpp
    source/idf/ThrustMaster.cpp
    source/idf/UsbChProPedals.cpp
    source/idf/UsbDevice.cpp
    source/idf/UsbDualShock3.cpp
    source/idf/UsbDualShock4.cpp
    source/idf/UsbDualShock.cpp
    source/idf/UsbExtreme3dPro.cpp
    source/idf/UsbGravis.cpp
    source/idf/UsbHagstromKEUSB36.cpp
    source/idf/UsbHagstromKEUSB36FS.cpp
    source/idf/UsbIndustrialProducts2.cpp
    source/idf/UsbIndustrialProducts3.cpp
    source/idf/UsbIndustrialProducts.cpp
    source/idf/UsbKeyboard.cpp
    source/idf/UsbMadCatz.cpp
    source/idf/UsbSaitek.cpp
    source/idf/UsbSpaceBase.cpp
    source/idf/UsbSpaceExplorer.cpp
    source/idf/UsbSpaceMouse.cpp
    source/idf/UsbSpaceNavigator.cpp
    source/idf/UsbWingMan.cpp
    source/idf/UsbXBox.cpp
    source/idf/Utils.cpp
    source/idf/VirtualLayout.cpp
    source/idf/WingMan.cpp
    source/idf/XBox.cpp
    source/idf/hidapi.c
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-show-option -Wredundant-decls -Wshadow -Woverloaded-virtual")

set_source_files_properties(hidapi.c PROPERTIES COMPILE_FLAGS "-Wno-sign-compare")

# ====================
# IDF
# ================
add_library(idf STATIC ${SRC_IDF})
include_directories("include" "include/hidapi/hidapi")

install(TARGETS idf
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
