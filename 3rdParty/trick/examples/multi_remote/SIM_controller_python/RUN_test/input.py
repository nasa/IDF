trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# import IDF's modules
import idf.config

# This dictionary facilitates looking up the class to instantiate for single,
# composite, and clients of each Controller type.
controllers = {
    'flight': {
      'single': trick.SingleFlightController,
      'composite': trick.CompositeFlightController,
      'client': trick.FlightControllerClient
    },
    'camera': {
      'single': trick.SingleCameraController,
      'composite': trick.CompositeCameraController,
      'client': trick.CameraControllerClient
    },
    'robotics': {
      'single': trick.SingleRoboticsController,
      'composite': trick.CompositeRoboticsController,
      'client': trick.RoboticsControllerClient
    }
}

# This dictionary contains the client configuration information present in the
# the S_define of SIM_controller.
sims = [
  # SIM_A
  [
    # RemoteFlightServer
    {
      # type of Controller we're working with
      'type': controllers['flight'],
      # Controller to drive the Client with
      'sourceController': example.simA_flightController,
      # port on which the Server is listening
      'port': 19000
    },
    # RemoteCameraServer
    {
      'type': controllers['camera'],
      'sourceController': example.simA_cameraController,
      'port': 19001
    }
  ],
  #SIM_B
  [
    {
      'type': controllers['flight'],
      'sourceController': example.simB_flightController,
      'port': 20000
    },
    {
      'type': controllers['robotics'],
      'sourceController': example.simB_roboticsController,
      'port': 20001
    }
  ]
]

# create the clients and add them to the IdfInputDeviceManager
for sim in sims:
    for system in sim:
        client = system['type']['client'](system['sourceController'], 'localhost', system['port'])
        client.thisown = False
        example.add(client)

# inherit from IDF's Configurator
class Configurator(idf.config.Configurator) :

    # this method is abstract in the base class, and so we must override it
    def addMasterDevice(self, device):

        # Despite being abstract in the base class, this method is nevertheless implemented there.
        # (It calls addInputDevice for you). Don't forget to call it!
        super(Configurator, self).addMasterDevice(device)

        # For each system, create a Controller and add it to the corresponding CompositeController.
        # Ensure only one Controller is active at a time.
        meg = trick.MutualExclusionGroup()
        meg.thisown = False
        for sim in sims:
            for system in sim:
                controller = self.createController(system['type']['single'], device)
                meg.add(controller)
                system['sourceController'].add(controller)

# instantiate a Configurator, passing it the IdfInputDeviceManager instance from the S_define
configurator = Configurator(example)
