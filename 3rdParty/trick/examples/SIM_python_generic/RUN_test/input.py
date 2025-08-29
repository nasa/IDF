trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# import IDF's modules
import idf.config

# inherit from IDF's Configurator
class Configurator(idf.config.Configurator) :

    # this method is abstract in the base class, and so we must override it
    def addMasterDevice(self, device):

        # Despite being abstract in the base class, this method is nevertheless implemented there.
        # (It calls addInputDevice for you). Don't forget to call it!
        super(Configurator, self).addMasterDevice(device)

# Instantiate a Configurator, passing it the IdfInputDeviceManager instance from the S_define.
configurator = Configurator(example, configFile="RUN_test/generic_hc_config.py")
