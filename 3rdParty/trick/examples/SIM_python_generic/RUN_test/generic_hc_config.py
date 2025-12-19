import sys
import traceback

# Instantiate a Generic Joystick using its Vendor ID, Product ID and Interface ID
# Use IDF/apps/hidScanner to assist with getting this information.
# In this example, we are creating a mapping for a
# Thrustmaster AVA Base: https://eshop.thrustmaster.com/en_us/ava-base.html
# with an F16 grip: https://eshop.thrustmaster.com/en_us/viper-hotas-add-on-grip.html
try:
   device = trick.HidGenericJoystick( 0x044F, 0x0415, 0 )
   device.thisown = 0
   self.addMasterDevice( device )
except Exception as e:
   print( "IDF init error:", traceback.format_exc() )
   sys.exit(1)

# Create a SingleFlightController, including compositing X, Y, and Z from buttons
# use IDF/apps/decoder to assist with figuring out which buttons to use

# this grip does not have a twist so we'll use some buttons
twist = trick.CompositeInput()
twist.thisown = 0
twist.addInput( device.getButton(14) )
twist.addInput( device.getButton(12), -1 )

x = trick.CompositeInput()
x.thisown = 0
x.addInput( device.getButton(15) )    # the buttons vector is zero indexed
x.addInput( device.getButton(17), -1 )

y = trick.CompositeInput()
y.thisown = 0
y.addInput( device.getButton(18) )
y.addInput( device.getButton(16), -1 )

z = trick.CompositeInput()
z.thisown = 0
z.addInput( device.getButton(7) )
z.addInput( device.getButton(9), -1 )

controller = trick.SingleFlightController(
   device.leftRightPivot,
   device.forwardBackwardPivot,
   twist,
   x, y, z
)
controller.roll.setInverted( True )
controller.pitch.setInverted( True )
controller.thisown = 0 # don't forget this!!


# add controller to the InputDeviceManager
self.inputDeviceManager.controller = controller