# Make IDF_HOME available to the sim at run time
export IDF_HOME ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../..)
export TRICK_GTE_EXT += IDF_HOME

# Header include paths
COMMON = -I${IDF_HOME}/include -I${IDF_HOME}/source
TRICK_CFLAGS   += ${COMMON}
TRICK_CXXFLAGS += ${COMMON}
TRICK_SFLAGS   += -I${IDF_HOME}/3rdParty/trick/sim_objects

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

DIRS = externals/idf/apps/vhc externals/idf/3rdParty/trick
LINKS = externals/idf/apps/vhc/build externals/idf/3rdParty/trick/python

build_externals: $(LINKS)

$(LINKS): | $(DIRS)
	ln -sf ${IDF_HOME}/3rdParty/trick/python externals/idf/3rdParty/trick/python
	ln -sf ${IDF_HOME}/apps/vhc/build externals/idf/apps/vhc/build

$(DIRS):
	mkdir -p externals/idf/apps/vhc
	mkdir -p externals/idf/3rdParty/trick

clean: clean_idf

clean_idf:
	rm -rf externals/idf
