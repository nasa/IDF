#ifndef _PYTHON_HEADERS_HH_
#define _PYTHON_HEADERS_HH_

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
#include "SingleFlightController.hh"
#include "CompositeFlightController.hh"
#include "RemoteFlightController.hh"

// CameraController
#include "SingleCameraController.hh"
#include "CompositeCameraController.hh"
#include "RemoteCameraController.hh"

// RoboticsController
#include "SingleRoboticsController.hh"
#include "CompositeRoboticsController.hh"
#include "RemoteRoboticsController.hh"

// Miscellaneous
#include "MutualExclusionGroup.hh"
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
#include "idf/UsbIndustrialProducts.hh"
#include "idf/UsbSaitek.hh"
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
