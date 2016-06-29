# Make IDF_HOME available to the sim at run time
export IDF_HOME ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../..)
export TRICK_GTE_EXT += IDF_HOME

# Header include paths
TRICK_CFLAGS   += -I${IDF_HOME}/models
TRICK_CXXFLAGS += -I${IDF_HOME}/models
TRICK_SFLAGS   += -I${IDF_HOME}/trick/sim_objects

# Library includes
ifeq (${TRICK_HOST_TYPE}, Linux)
    TRICK_USER_LINK_LIBS += -ludev -lrt
else ifeq (${TRICK_HOST_TYPE}, Darwin)
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif

# Include libntcan, if available
ifdef NTCAN_HOME
    TRICK_CFLAGS         += -I${NTCAN_HOME} -DIDF_CAN
    TRICK_CXXFLAGS       += -I${NTCAN_HOME} -DIDF_CAN
    TRICK_USER_LINK_LIBS += -L${NTCAN_HOME} -lntcan
endif
