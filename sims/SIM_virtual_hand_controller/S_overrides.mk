MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
common = -I${IDF_HOME}/models
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}
TRICK_SFLAGS += -I${IDF_HOME}/sims/sim_objects

ifeq (${TRICK_HOST_TYPE}, Linux)
    TRICK_USER_LINK_LIBS += -ludev -lrt
else ifeq (${TRICK_HOST_TYPE}, Darwin)
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif

# Make IDF_HOME available to the S_main executable. Note that IDF_HOME must ALSO be exported.
export TRICK_GTE_EXT += IDF_HOME
