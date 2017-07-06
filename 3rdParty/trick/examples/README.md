This directory contains example Trick simulations using IDF. They start by
demonstrating basic functionality and increase in complexity down the list.

### SIM_device_only
Demonstrates reading normalized values from a Logitech Extreme 3D Pro USB
Joystick. If you only need to program against a specific device, this example
is all you need.

### SIM_device_and_controller
Demonstrates mapping the inputs from a Logitech Extreme 3D Pro USB Joystick to a
generalized flight controller interface. If you want to write your control code
such that it works with many different devices, you will want to program against
a domain-specific controller rather than a particular physical device.

### SIM_virtual_hand_controller
Demonstrates using the
[Virtual Hand Controller](https://github.com/nasa/IDF/wiki/Virtual-Hand-Controller),
which is a Java application that can serve as a basic six degree of freedom
device. The VHC is often useful when you don't have any physical devices handy.
Like the `SIM_device_only`, this example illustrates directly reading from the
device without regard for any controller interface. This example launches the
VHC from the `S_define`.

### SIM_virtual_hand_controller_python
Demonstrates using the
[Virtual Hand Controller](https://github.com/nasa/IDF/wiki/Virtual-Hand-Controller),
which is a Java application that can serve as a basic six degree of freedom
device. The VHC is often useful when you don't have any physical devices handy.
Like the `SIM_device_only`, this example illustrates directly reading from the
device without regard for any controller interface. This example uses IDF's
Python module to launch the VHC from the input file.

### SIM_python1
Demonstrates using the Python class `idf.config.Configurator` to automatically
select the first available device and create a `Controller` from it.

### SIM_composite_controller
Demonstrates using a CompositeController to allow multiple controllers to
service the same interface. Controllers can be dynamically added and removed,
and all inputs are combined. In general, you should prefer CompositeControllers
over single Controllers as it offers increased flexibility.

### multi_remote
Demonstrates use of the `Server` and `Client` class templates to read from a
device in one sim and connect it to multiple Controllers in multiple other sims.
See `multi_remote/README.md` for more details.
