# This makefile sets up variables and rules common to all other makefiles.
# The user need not include this from their S_overrides.mk.

# Make IDF_HOME available to the sim at run time
export IDF_HOME := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../..)
TRICK_GTE_EXT += IDF_HOME

# Header, SimObject, and Python module paths
EXTERNALS         := externals/idf
THIRD_PARTY       := $(IDF_HOME)/3rdParty/trick
CONFIG            := $(IDF_HOME)/bin/idf-config
COMMON		  := $(shell $(CONFIG) --cxxflags) -I$(IDF_HOME)/include/hidapi/hidapi -Wno-implicit-conversion-floating-point-to-bool
TRICK_CFLAGS      += $(COMMON)
TRICK_CXXFLAGS    += $(COMMON)
TRICK_SFLAGS      += -I$(THIRD_PARTY)/sim_objects
TRICK_PYTHON_PATH += :$(EXTERNALS)/3rdParty/trick/python:$(THIRD_PARTY)/python
TRICK_EXCLUDE     += :$(IDF_HOME)/include/hidapi

# Links to be built by build_externals
LINKS := $(EXTERNALS)/apps/vhc/build $(EXTERNALS)/3rdParty/trick/python

# Libraries
TRICK_LDFLAGS += $(shell $(CONFIG) --libs)

# Include libntcan, if available
ifdef NTCAN_HOME
    TRICK_CFLAGS   += -I$(NTCAN_HOME) -DIDF_CAN
    TRICK_CXXFLAGS += -I$(NTCAN_HOME) -DIDF_CAN
    TRICK_LDFLAGS  += -L$(NTCAN_HOME) -lntcan
endif

build_externals: $(LINKS)

$(dir $(LINKS)):
	@mkdir -p $@

clean: clean_idf

clean_idf:
	@rm -rf externals/idf

.SECONDEXPANSION:

$(LINKS): $(EXTERNALS)% : $(IDF_HOME)% | $$(dir $$@)
	@ln -s $< $@

.PHONY: clean_idf
