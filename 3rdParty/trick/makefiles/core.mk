# This makefile causes Trick to directly build IDF's source code as part of a
# simulation build, just like any other model code. This is the normal,
# non-Trickified version.

include $(dir $(lastword $(MAKEFILE_LIST)))/common.mk

# Trick will be building all of IDF, so we need to add the path for use with LIBRARY_DEPENDENCY
SOURCE := $(IDF_HOME)/source
TRICK_CFLAGS   += -I$(SOURCE)
TRICK_CXXFLAGS += -I$(SOURCE)
