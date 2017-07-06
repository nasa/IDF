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

        # for each server, create a Controller using the default mapping
        simA_flightController = self.createController(trick.SingleFlightController, device)
        simA_cameraController = self.createController(trick.SingleCameraController, device)
        simB_flightController = self.createController(trick.SingleFlightController, device)
        simB_roboticsController = self.createController(trick.SingleRoboticsController, device)

        # ensure only one Controller is active at a time
        meg = trick.MutualExclusionGroup()
        meg.thisown = False
        meg.add(simB_flightController)
        meg.add(simB_roboticsController)
        meg.add(simA_cameraController)
        meg.add(simA_flightController)

        # add each Controller to the correpsonding CompositeController
        self.inputDeviceManager.simA_flightController.add(simA_flightController)
        self.inputDeviceManager.simA_cameraController.add(simA_cameraController)
        self.inputDeviceManager.simB_flightController.add(simB_flightController)
        self.inputDeviceManager.simB_roboticsController.add(simB_roboticsController)

# instantiate a Configurator, passing it the IdfInputDeviceManager instance from the S_define
configurator = Configurator(example)
