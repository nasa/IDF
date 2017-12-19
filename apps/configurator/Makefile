UNAME := $(shell uname)
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
CFLAGS = -g -Wall -I${IDF_HOME}/include
BUILD_DIR := $(IDF_HOME)/build
LIB_IDF := $(BUILD_DIR)/libidf.a
LIB_HID := $(BUILD_DIR)/libhidapi.a
MAKEFILE := $(BUILD_DIR)/Makefile

ifeq ($(UNAME), Linux)
    LIBS = -ludev -lrt
else ifeq ($(UNAME), Darwin)
    LIBS = -framework IOKit -framework CoreFoundation
endif

configurator: Configurator.cpp $(LIB_IDF) $(LIB_HID)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(LIB_IDF): $(MAKEFILE)
	make -C $(BUILD_DIR)

$(LIB_HID): $(MAKEFILE)
	make -C $(BUILD_DIR)  hidapi

$(MAKEFILE): | $(BUILD_DIR)
	cd $(BUILD_DIR); cmake ..

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf configurator
