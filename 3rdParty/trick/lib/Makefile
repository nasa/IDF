ifndef TRICK_HOME
    $(error TRICK_HOME must be set)
endif

TRICKIFY := $(TRICK_HOME)/share/trick/makefiles/trickify.mk

ifeq ($(wildcard $(TRICKIFY)),)
    $(error This makefile requires at least Trick 17.1)
endif

INCLUDE := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../../../include)
export TRICKIFY_OBJECT_NAME := trickified_idf.o
export TRICKIFY_CXX_FLAGS := -I$(INCLUDE)
export TRICK_EXCLUDE := :$(INCLUDE)/hidapi

all:
	@$(MAKE) -s -f $(TRICKIFY)

clean:
	@rm -rf build python trick $(TRICKIFY_OBJECT_NAME)
