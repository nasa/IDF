MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
common = -I$(abspath $(MAKEFILE_DIR)/../..)/models
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}

ifeq (${TRICK_HOST_TYPE}, Linux)
    TRICK_USER_LINK_LIBS += -ludev -lrt
else ifeq (${TRICK_HOST_TYPE}, Darwin)
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif
