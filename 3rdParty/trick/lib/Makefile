ifndef TRICK_HOME
    $(error TRICK_HOME must be set)
endif

TRICKIFY := $(TRICK_HOME)/share/trick/makefiles/trickify.mk

ifeq ($(wildcard $(TRICKIFY)),)
    $(error This makefile requires at least Trick 17.1)
endif

export TRICKIFY_OBJECT_NAME = trickified_idf.o
export TRICKIFY_CXX_FLAGS = -I$(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../../include)

all:
	@$(MAKE) -s -f $(TRICKIFY)

clean:
	@rm -rf build python trick $(TRICKIFY_OBJECT_NAME)
