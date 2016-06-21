MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
common = -I${IDF_HOME}/models
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}
TRICK_SFLAGS += -I${IDF_HOME}/sims/sim_objects

ifeq (${TRICK_HOST_TYPE}, Linux)
    TRICK_USER_LINK_LIBS += -ludev -lrt
else ifeq (${TRICK_HOST_TYPE}, Darwin)
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif
