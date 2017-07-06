This suite demonstrates use of the `Server` and `Client` class templates to
read from a device in one sim and connect it to multiple Controllers in multiple
other sims.

### SIM_A
Contains a `FlightControllerServer` and `CameraControllerServer`, allowing
remote devices to connect via sockets. The `Server`s are instantiated directly
in the `S_define`.

### SIM_B
Contains a `FlightControllerServer` and `RoboticsControllerServer`, allowing
remote devices to connect via sockets. These controllers are separate and
unrelated to those in `SIM_A`. The `S_define` instantiates
`CompositeController`s, and the `Server`s are instantiated in the input file.
This architecture allows both local and remote devices to be mapped to the same
`Controller`.

### SIM_controller
Contains a `CompositeController` for each `Server` in `SIM_A` and `SIM_B`. Each
`CompositeController` drives a `Client` that connects to the corresponding
`Server` in `SIM_A` or `SIM_B`. The `Client`s are configured in the `S_define`.

### SIM_controller_python
Identical to `SIM_controller` except that the `Client`s are configured in the
input file.
