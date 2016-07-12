trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# import IDF's modules
sys.path.append(os.environ['IDF_HOME'] + "/trick/python")
import idf.config

# inherit from IDF's Configurator
class Configurator(idf.config.Configurator) :

    # this method is abstract in the base class, and so we must override it
    def addMasterDevice(self, device):

        # Despite being abstract in the base class, this method is nevertheless implemented there.
        # (It calls addInputDevice for you). Don't forget to call it!
        super(Configurator, self).addMasterDevice(device)

        # create a Controller and add it to the CompositeController
        self.inputDeviceManager.controller.add(self.createController(trick.SingleFlightController, device))

# Instantiate a Configurator, passing it the IdfInputDeviceManager instance from the S_define.
configurator = Configurator(example)

# Because we used a CompositeController in the S_define, we can add any number of devices, and
# their commands will be combined. Normally, this would be done in ~/.idf/config.py.
# See https://github.com/nasa/IDF/wiki/Trick-Integration#python-module for details.
#
# ~/.idf/config.py:
# self.addMasterDevice(trick.UsbSpaceNavigator())
# self.addMasterDevice(trick.UsbWingMan())
# self.addMasterDevice(trick.UsbDualShock4())
