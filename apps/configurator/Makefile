UNAME := $(shell uname)
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
MODEL_DIR := $(IDF_HOME)/models
CFLAGS = -g -Wall -I$(MODEL_DIR)
LIB_IDF := $(IDF_HOME)/build/lib/libidf.a

ifeq ($(UNAME), Linux)
    LIBS = -ludev -lrt
else ifeq ($(UNAME), Darwin)
    LIBS = -framework IOKit -framework CoreFoundation
endif

configurator: Configurator.cpp $(LIB_IDF)
	$(CXX) -o $@ $^ $(CFLAGS) $(LIBS)

$(LIB_IDF):
	$(MAKE) -C $(IDF_HOME)

clean:
	rm -rf configurator
