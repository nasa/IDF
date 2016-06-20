UNAME := $(shell uname)
MODEL_DIR = models
BUILD_DIR = build
OBJECT_DIR = $(BUILD_DIR)/objects
LIB = $(BUILD_DIR)/lib/libidf.a
SRC_DIRS = $(MODEL_DIR)/simulationInterface $(MODEL_DIR)/inputAbstraction $(MODEL_DIR)/hardwareInterface
SOURCES := $(MODEL_DIR)/simulationInterface/src/RoboticsController.cpp
#SOURCES := $(shell find $(SRC_DIRS) -name "*.cpp" -not -path "*/io_src/*" -not -path "*/swig/*")
ifndef IDF_CAN
SOURCES := $(filter-out $(shell find $(MODEL_DIR)/hardwareInterface -name "*Can*"),$(SOURCES))
endif
OBJECTS := $(SOURCES:$(MODEL_DIR)/%.cpp=$(OBJECT_DIR)/%.o)
CPPFLAGS += -std=c++11 -g -Wall -Wextra -I$(MODEL_DIR)

ifeq ($(UNAME), Linux)
CPPFLAGS += -I/usr/include/libusb-1.0
endif

all: $(LIB)

clean:
	rm -rf $(BUILD_DIR)

$(sort $(dir $(OBJECTS))) $(dir $(LIB)):
	mkdir -p $@

$(LIB): $(OBJECTS) | $(dir $(LIB))
	ar rs $(LIB) $(OBJECTS)

.SECONDEXPANSION:

$(OBJECT_DIR)/%.o: $(MODEL_DIR)/%.cpp | $$(dir $$@)
	$(CXX) -c $(CPPFLAGS) -o $@ $^
