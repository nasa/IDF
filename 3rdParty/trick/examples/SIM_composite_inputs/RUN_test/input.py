trick.real_time_enable()
trick.exec_set_software_frame(0.1)

# Instantiate the keyboard. Make sure you change the arguments to match your keyboard's
# vendor and product IDs
keyboard = trick.UsbKeyboard(0x413C, 0x2101)
example.add(keyboard)

# SingleFlightController's construtor takes the six Inputs we want to use for roll, pitch, yaw,
# x, y, and z. To form a SingleInput from two keyboard keys, we use a CompositeInput.
roll = trick.CompositeInput()
# command positive roll when we press numpad 9
roll.addInput(keyboard.keypad9)
# negate this input so that we command negative roll when we press numpad 7
roll.addInput(keyboard.keypad7, -1)

pitch = trick.CompositeInput()
pitch.addInput(keyboard.keypad8)
pitch.addInput(keyboard.keypad2, -1)

yaw = trick.CompositeInput()
yaw.addInput(keyboard.keypad4)
yaw.addInput(keyboard.keypad6, -1)

x = trick.CompositeInput()
x.addInput(keyboard.keypadAdd)
x.addInput(keyboard.keypadSubtract, -1)

y = trick.CompositeInput()
y.addInput(keyboard.leftArrow)
y.addInput(keyboard.rightArrow, -1)

z = trick.CompositeInput()
z.addInput(keyboard.upArrow)
z.addInput(keyboard.downArrow, -1)

# create a SingleFlightController with the CompositeInputs above and add it to the sim object
controller = trick.SingleFlightController(roll, pitch, yaw, x, y, z)
example.controller.add(controller)
