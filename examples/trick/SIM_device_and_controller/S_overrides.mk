SIM_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(SIM_DIR)/../../..)
common = -I${IDF_HOME}/models
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}
TRICK_SFLAGS += -I${IDF_HOME}/trick/sim_objects

ifeq (${TRICK_HOST_TYPE}, Linux)
    TRICK_USER_LINK_LIBS += -ludev -lrt
else ifeq (${TRICK_HOST_TYPE}, Darwin)
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif
