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
#include "inputAbstraction/include/CompositeInput.hh"
#include "inputAbstraction/include/Deadband.hh"

// Remote Devices
#include "hardwareInterface/include/RemoteExtreme3dPro.hh"
#include "hardwareInterface/include/RemoteSpaceNavigator.hh"

// Serial Devices
#include "hardwareInterface/include/SerialThrustMaster.hh"
#include "hardwareInterface/include/SerialThrustMaster2.hh"

// USB Devices
#include "hardwareInterface/include/UsbChProPedals.hh"
#include "hardwareInterface/include/UsbDualShock3.hh"
#include "hardwareInterface/include/UsbDualShock4.hh"
#include "hardwareInterface/include/UsbExtreme3dPro.hh"
#include "hardwareInterface/include/UsbGravis.hh"
#include "hardwareInterface/include/UsbIndustrialProducts.hh"
#include "hardwareInterface/include/UsbSaitek.hh"
#include "hardwareInterface/include/UsbSpaceExplorer.hh"
#include "hardwareInterface/include/UsbSpaceMouse.hh"
#include "hardwareInterface/include/UsbSpaceNavigator.hh"
#include "hardwareInterface/include/UsbWingMan.hh"
#include "hardwareInterface/include/UsbXBox.hh"

// CAN Devices
#ifdef IDF_CAN
#include "hardwareInterface/include/CanIndustrialProducts.hh"
#endif

#endif
