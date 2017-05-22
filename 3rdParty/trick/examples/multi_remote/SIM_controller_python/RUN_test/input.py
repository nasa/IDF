trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# import IDF's modules
import idf.config

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

sims = [
  [
    {
      'type': controllers['flight'],
      'compositeController': example.simA_flightController,
      'port': 19000
    },
    {
      'type': controllers['camera'],
      'compositeController': example.simA_cameraController,
      'port': 19001
    }
  ],
  [
    {
      'type': controllers['flight'],
      'compositeController': example.simB_flightController,
      'port': 20000
    },
    {
      'type': controllers['robotics'],
      'compositeController': example.simB_roboticsController,
      'port': 20001
    }
  ]
]

for sim in sims:
    for system in sim:
        client = system['type']['client'](system['compositeController'], 'localhost', system['port'])
        client.thisown = False
        example.add(client)

# inherit from IDF's Configurator
class Configurator(idf.config.Configurator) :

    # this method is abstract in the base class, and so we must override it
    def addMasterDevice(self, device):

        # Despite being abstract in the base class, this method is nevertheless implemented there.
        # (It calls addInputDevice for you). Don't forget to call it!
        super(Configurator, self).addMasterDevice(device)

        # create a controller using the default mapping and assign it to the pointer in the SimObject
        meg = trick.MutualExclusionGroup()
        meg.thisown = False
        for sim in sims:
            for system in sim:
                controller = self.createController(system['type']['single'], device)
                meg.add(controller)
                system['compositeController'].add(controller)

# Instantiate a Configurator, passing it the IdfInputDeviceManager instance from the S_define.
configurator = Configurator(example)
