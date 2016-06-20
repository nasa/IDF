UNAME := $(shell uname)
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
MODEL_DIR := $(IDF_HOME)/models
CFLAGS = -g -Wall -I$(MODEL_DIR)

ifeq ($(UNAME), Linux)
    HID_C := $(MODEL_DIR)/hidapi/linux/hid.c
    LIBS += -ludev
else ifeq ($(UNAME), Darwin)
    HID_C := $(MODEL_DIR)/hidapi/max/hid.c
    LIBS += -framework IOKit -framework CoreFoundation
endif

hidScanner: hidScanner.c
	$(CC) -o $@ $^ $(HID_C) $(CFLAGS) $(LIBS)

clean:
	rm -rf hidScanner

