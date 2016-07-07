This directory contains example Trick simulations using IDF. They start by
demonstrating basic functionality and increase in complexity down the list.

1. SIM_device_only
Demonstrates reading normalized values from a Logitech Extreme 3D Pro USB
Joystick. If you only need to program against a specific device, this example
is all you need.

2. SIM_device_and_controller
Demonstrates mapping the inputs from a Logitech Extreme 3D Pro USB Joystick to a
generalized flight controller interface. If you want to write your control code
such that it works with many different devices, you will want to program against
a domain-specific controller rather than a particular physical device.

3. SIM_virtual_hand_controller
Demonstrates using the Virtual Hand Controller, which is a Java application
that can serve as a basic six degree of freedom device. The VHC is often
useful when you don't have any physical devices handy. Like the SIM_device_only,
this example illustrates directly reading from the device without regard for any
controller interface.

4. SIM_python1
Demonstrates using the Python class idf.config.Configurator to automatically
select the first available device and create a Controller from it.
