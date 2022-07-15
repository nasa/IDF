import abc
import inspect
import os
import socket
import sys
import trick

## provides convenience functions for setting up an IDF infrastructure via Python
#
# This class assumes the use of a number of C++ classes, links to which are provided in the Doxygen documentation.
class Configurator:

    # mark this class as abstract
    __metaclass__ = abc.ABCMeta

    ## constructor
    #
    # @param self the object pointer
    # @param deviceManager @copydoc inputDeviceManager
    # @param vhcVariableName @copydoc vhcVariable
    # @param configFile the configuration file
    def __init__(self, deviceManager, vhcVariableName=None, configFile=os.path.join(os.path.expanduser('~'), '.idf', 'config.py')):
        self.inputDeviceManager = deviceManager
        self.vhcVariable = vhcVariableName

        # execute the user configuration file if present
        if not self.execConfigFile(configFile):

            # otherwise, use the first available device
            self.useFirstAvailableDevice()

    ## adds the first available USB device. This will connect only one device and will use the default mapping. Devices without a default mapping
    # will be skipped. If no device is successfully mapped, the Virtual Hand %Controller will be launched.
    #
    # @param self the object pointer
    #
    # @return the first available USB device, or @c None if none was found
    def useFirstAvailableDevice(self):

        # loop through all supported devices
        for device in [
          trick.UsbChProPedals,
          trick.UsbDualShock3,
          trick.UsbDualShock4,
          trick.UsbExtreme3dPro,
          trick.UsbGravis,
          trick.UsbIndustrialProducts,
          trick.UsbIndustrialProducts3,
          trick.UsbSaitek,
          trick.UsbSaitekX52,
          trick.UsbSaitekX56Stick,
          trick.UsbSaitekX56Throttle,
          trick.UsbSpaceExplorer,
          trick.UsbSpaceMouse,
          trick.UsbSpaceNavigator,
          trick.UsbTeensyduino,
          trick.UsbWingMan,
          trick.UsbXBox]:
            device = device()
            # if the device is connected to the computer, add it and return
            if int(device.isConnected()):
                self.addMasterDevice(device)
                return device

        # No device was found. If the Launch the Virtual Hand Controller if supported.
        if (self.vhcVariable is not None):
            launchVirtualController(self.vhcVariable)

        return None

    ## adds @a inputDevice to #inputDeviceManager
    #
    # @param self the object pointer
    # @param inputDevice the input device to add
    def addInputDevice(self, inputDevice):
        inputDevice.thisown = 0
        self.inputDeviceManager.add(inputDevice)
        return

    ## creates a new Controller mapped to @a inputDevice and calls {@link addInputDevice}(<em>inputDevice</em>)
    #
    # @param self the object pointer
    # @param controllerClass the type of controller to create
    # @param inputDevice the input device to map to the controller
    #
    # @return the controller instance
    def createController(self, controllerClass, inputDevice) :
        controller = controllerClass.createInstance(inputDevice)
        controller.thisown = 0
        self.addInputDevice(inputDevice)
        return controller

    ## creates a Controller for each control system and maps it to @a inputDevice using default mappings.
    # Calls {@link addInputDevice}(<em>inputDevice</em>)
    #
    # @param self the object pointer
    # @param inputDevice the input device to map
    # @param kwargs a dictionary of keyword arguments for use by subclasses. This class ignores it.
    @abc.abstractmethod
    def addMasterDevice(self, inputDevice, **kwargs):
        self.addInputDevice(inputDevice)
        return

    ## sets all InputDevice's delays in seconds
    #
    # @param self the object pointer
    # @param delay the delay in seconds
    def setDelay(self, delay = 0):
        self.inputDeviceManager.setDelay(delay)
        return

    ## calls @c exec on @a fileName
    #
    # @param fileName the name of the file to @c exec
    #
    # @return @c true if the file was found
    def execConfigFile(self, fileName):
        try:
            exec(compile(open(fileName).read(), fileName, 'exec'))
        except (IOError, TypeError):
            return False
        return True

    ## @var inputDeviceManager
    # an instance of IdfInputDeviceManager to which {@link InputDevice}s will be added

    ## @var vhcVariable
    # the name of an instance of VirtualLayout whose values the Virtual Hand %Controller will set

## launches the Java Virtual Hand %Controller
#
# @param vhcVariable @copydoc Configurator::vhcVariable
def launchVirtualController(vhcVariable):
    vhc = trick.ExternalApplication()
    vhc.thisown = 0
    trick.add_external_application(vhc)
    vhc.add_arguments('--disconnectBehavior Close --simObjectName ' + str(vhcVariable) + ' --translationOrientation XYZ --rotationOrientation RYP --invertX false --invertY true --invertZ false --invertRoll true --invertPitch true --invertYaw true --xMin -100 --xMax 100 --yMin -100 --yMax 100 --zMin -100 --zMax 100 -rollMin -100 --rollMax 100 --pitchMin -100 --pitchMax 100 --yawMin -100 --yawMax 100')

    executable = os.path.abspath(os.path.dirname(inspect.getsourcefile(lambda:0)) + '/../../../../apps/vhc/build') + '/'
    if sys.platform == 'darwin':
        vhc.set_startup_command('open ' + executable + 'VHC.app --args')
    else:
        vhc.set_startup_command('java -jar ' + executable + 'VirtualHandController.jar')

    return

## creates a MutualExclusionGroup and adds all @a controllers
#
# @param controllers an iterable of {@link Controller}s
#
# @return the newly-created MutualExclusionGroup
def makeMutuallyExclusive(controllers):
    mutualExclusionGroup = trick.MutualExclusionGroup()
    mutualExclusionGroup.thisown = 0
    for controller in controllers:
        mutualExclusionGroup.add(controller)
    return mutualExclusionGroup
