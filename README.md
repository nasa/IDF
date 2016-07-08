# Input Device Framework

IDF is a software library that provides an infrastructure for interfacing
software with physical input devices. Examples of common devices include hand
controllers, joysticks, foot pedals, computer mice, game controllers, etc.
Conceptually, the framework can be extended to support any device that produces
digital output. IDF additionally presents, and is itself an implementation of, a
design methodology that encourages application developers to program against
domain-specific interfaces rather than particular hardware devices. This
abstraction frees the application from the details of communicating with the
underlying devices, resulting in robust and flexible code that is
device-agnostic. IDF ensures that devices meet application interface
requirements, supports many-to-many relationships between application interfaces
and devices, allows for flexible and dynamic interpretation of device inputs,
and provides methods for transforming and combining inputs.

# The Problem

Software often requires input from external physical devices. The range of
devices, data formats, and mediums of communication are virtually limitless.
There thus exists a need for a method by which to deliver data to applications
in a consistent, well-defined manner, and in an application-defined format. The
vast array of ways that devices output data necessitates a separation between
the application, which is concerned only with what the data represents, and the
devices themselves, which have no notion of how their data is to be used. There
must then be a way to bridge this disconnect without burdening either side with
details of the other. Barring such a tool, applications may be written against
specific devices, but this pollutes the program's primary functionality with a
secondary task and forces the application interface to conform to the device's
output format. As the consumer of the data, it is preferable for the
application to define its own context-specific interface through which the data
is received. Changes in the device, data format, or communication medium should
not alter the application interface.

# A Solution

IDF serves to completely separate the "business" logic of a program from the
logic responsible for reading raw input from physical devices. Beyond simply
isolating the code, it further aims to abstract each side from the other, so
that both pieces can be developed fully independently. Its goal is to enable
application developers to write robust, flexible code with clearly delineated
interface points which are defined in a domain and context most meaningful to
the application.

# Architectural Summary

Conceptually, IDF consists of three layers:

### Simulation Interface Layer

This layer defines the point at which external inputs enter the application's
primary functional logic. It is here that a developer decides what kind of
inputs his system will accept, and in what format it will accept them. Once this
interface is established, the developer encodes it as it a "controller" by
extending IDF and specializing it for this particular application. Devices that
wish to service this interface must meet this controller's contract. This layer
is the only one with which the primary functional logic should interact.

### Hardware Interface Layer

This layer represents the physical input devices and is responsible for all
aspects of communication with the hardware, primarily reading and decoding raw
data. Devices are classified by their communication medium, and a representation
exists for each specific device supported.

### Input Abstraction Layer

This layer provides a means by which to tie the above two layers together. It
represents device input layouts without regard to their particular medium of
communication. A device's available data, represented in this layer, is
populated by the Hardware Interface Layer as it is received from the physical
device. This data can then be presented to a controller from the Simulation
Interface Layer, provided that it can be made to meet that controller's
contract.

# Wiki

See the [wiki](https://github.com/nasa/IDF/wiki) for installation instructions
and additional topics.

# License
IDF is released under the [NASA Open Source Agreement, Version 1.3](LICENSE).
