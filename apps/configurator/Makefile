UNAME := $(shell uname)
MAKEFILE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
IDF_HOME := $(abspath $(MAKEFILE_DIR)/../..)
CFLAGS = -g -Wall -I${IDF_HOME}/include
BUILD_DIR := $(IDF_HOME)/build
CMAKEFILE := $(BUILD_DIR)/Makefile
LIB_IDF := $(BUILD_DIR)/libidf.a

ifeq ($(UNAME), Linux)
    LIBS = -ludev -lrt
else ifeq ($(UNAME), Darwin)
    LIBS = -framework IOKit -framework CoreFoundation
endif

configurator: Configurator.cpp $(LIB_IDF)
	@$(CXX) -o $@ $(CFLAGS) $(LIBS) $^

$(BUILD_DIR):
	@mkdir -p $@

$(CMAKEFILE): | $(BUILD_DIR)
	@cd $(BUILD_DIR); cmake ..

$(LIBIDF): $(CMAKEFILE)
	@$(MAKE) -s -C $(dir $(CMAKEFILE))

clean:
	@rm -rf configurator
