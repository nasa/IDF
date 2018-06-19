UNAME := $(shell uname)
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
INCLUDE_DIR := $(IDF_HOME)/include
CFLAGS = -g -Wall -I$(INCLUDE_DIR)

ifeq ($(UNAME), Linux)
    HID_C := $(INCLUDE_DIR)/hidapi/linux/hid.c
    LIBS += -ludev
else ifeq ($(UNAME), Darwin)
    HID_C := $(INCLUDE_DIR)/hidapi/mac/hid.c
    LIBS += -framework IOKit -framework CoreFoundation
endif

hidScanner: hidScanner.c
	$(CXX) -o $@ $^ $(HID_C) $(CFLAGS) $(LIBS)

clean:
	rm -rf hidScanner

