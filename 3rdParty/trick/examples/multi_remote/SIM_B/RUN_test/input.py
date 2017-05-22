trick.real_time_enable()
trick.exec_set_software_frame(0.1)

flightServer = trick.FlightControllerServer(20000)
flightServer.thisown = False
example.add(flightServer)
example.flightController.add(flightServer)

roboticsServer = trick.RoboticsControllerServer(20001)
roboticsServer.thisown = False
example.add(roboticsServer)
example.roboticsController.add(roboticsServer)
