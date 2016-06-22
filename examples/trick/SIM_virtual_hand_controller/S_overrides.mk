SIM_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export IDF_HOME := $(abspath $(SIM_DIR)/../../..)
common = -I${IDF_HOME}/models
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}

# Make IDF_HOME available to the S_main executable. Note that IDF_HOME must ALSO be exported.
export TRICK_GTE_EXT += IDF_HOME
