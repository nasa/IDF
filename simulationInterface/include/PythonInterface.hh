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
 * @author Derek Bankieris
 */

#include "CompositeCameraController.hh"
#include "CompositeFlightController.hh"
#include "MutualExclusionGroup.hh"
#include "SingleCameraController.hh"
#include "SingleFlightController.hh"

#include "inputAbstraction/include/CompositeInput.hh"
#include "inputAbstraction/include/Deadband.hh"

#include "hardwareInterface/include/CanIndustrialProducts.hh"
#include "hardwareInterface/include/UsbChProPedals.hh"
#include "hardwareInterface/include/UsbGravis.hh"
#include "hardwareInterface/include/UsbIndustrialProducts.hh"
#include "hardwareInterface/include/UsbSaitek.hh"
#include "hardwareInterface/include/UsbSpaceExplorer.hh"
#include "hardwareInterface/include/UsbSpaceNavigator.hh"
#include "hardwareInterface/include/UsbWingMan.hh"
#include "hardwareInterface/include/UsbXBox.hh"
#include "hardwareInterface/include/UsbDualShock3.hh"

#endif
