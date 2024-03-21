IDF_HOME := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/../..)
IDF_CONFIG := $(IDF_HOME)/bin/idf-config
IDF_BUILD_DIR := $(IDF_HOME)/build
IDF_LIB := $(IDF_BUILD_DIR)/libidf.a

CXXFLAGS += $(shell $(IDF_CONFIG) --cxxflags)
LDLIBS += $(shell $(IDF_CONFIG) --libs)

hidScanner: $(IDF_LIB)

$(IDF_LIB): | $(IDF_BUILD_DIR)
	cd $| && cmake .. && $(MAKE)

$(IDF_BUILD_DIR):
	mkdir -p $@

clean:
	@rm -rf hidScanner
