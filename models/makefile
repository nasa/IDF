MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
SRC_DIRS = simulationInterface inputAbstraction hardwareInterface sim_services
OBJECT_DIR = objects
SOURCES := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJECTS := $(SOURCES:%.cpp=%.o)
CPPFLAGS += -g -Wall -Wextra -I. -I/usr/include/libusb-1.0

all: libidf.a

libidf.a: $(OBJECTS)
	ar rs libidf.a $(OBJECTS)

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS) libidf.a
