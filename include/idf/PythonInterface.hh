#ifndef PYTHON_INTERFACE_HH
#define PYTHON_INTERFACE_HH

/**
 * this file provides support for Python-instantiation of Input Device
 * Framework classes in Trick simulations. To be able to instantiate classes
 * in a Ptyhon script, CP must have processed the corresponding headers,
 * meaning the S_define must include those headers at some level. This file
 * provides an easy way to ensure that all appropriate IDF headers are
 * processed.
 *
 * Support for various device types here is modular. Serial and USB devices are
 * included by default. Support for other device classes must be explicitly
 * requested via definition of preprocessor symbols found below. This should
 * typically be done with -D options in your TRICK_CFLAGS or TRICK_CXXFLAGS.
 *
 * @author Derek Bankieris
 */

// FlightController
#include "idf/SingleFlightController.hh"
#include "idf/CompositeFlightController.hh"
#include "idf/RemoteFlightController.hh"

// CameraController
#include "idf/SingleCameraController.hh"
#include "idf/CompositeCameraController.hh"
#include "idf/RemoteCameraController.hh"

// RoboticsController
#include "idf/SingleRoboticsController.hh"
#include "idf/CompositeRoboticsController.hh"
#include "idf/RemoteRoboticsController.hh"

// Miscellaneous
#include "idf/MutualExclusionGroup.hh"
#include "idf/CompositeInput.hh"
#include "idf/Deadband.hh"

// Remote Devices
#include "idf/RemoteExtreme3dPro.hh"
#include "idf/RemoteSpaceNavigator.hh"

// Serial Devices
#include "idf/SerialThrustMaster.hh"
#include "idf/SerialThrustMaster2.hh"

// USB Devices
#include "idf/UsbChProPedals.hh"
#include "idf/UsbDualShock3.hh"
#include "idf/UsbDualShock4.hh"
#include "idf/UsbExtreme3dPro.hh"
#include "idf/UsbGravis.hh"
#include "idf/UsbHagstromKEUSB36.hh"
#include "idf/UsbHagstromKEUSB36FS.hh"
#include "idf/UsbIndustrialProducts.hh"
#include "idf/UsbIndustrialProducts2.hh"
#include "idf/UsbIndustrialProducts3.hh"
#include "idf/UsbKeyboard.hh"
#include "idf/UsbSaitek.hh"
#include "idf/UsbSaitekX52.hh"
#include "idf/UsbSpaceExplorer.hh"
#include "idf/UsbSpaceMouse.hh"
#include "idf/UsbSpaceNavigator.hh"
#include "idf/UsbWingMan.hh"
#include "idf/UsbXBox.hh"

// CAN Devices
#ifdef IDF_CAN
#include "idf/CanIndustrialProducts.hh"
#endif

#endif
