INCLUDE_DIR := include
SOURCE_DIR := source
BUILD_DIR := build
OBJECT_DIR := $(BUILD_DIR)/objects
DEPENDENCY_DIR := $(BUILD_DIR)/dependencies
LIB := $(BUILD_DIR)/lib/libidf.a
SOURCES := $(shell find $(SOURCE_DIR) -name "*.cpp" -not -path "*/io_src/*" -not -path "*/swig/*")
ifndef IDF_CAN
SOURCES := $(filter-out $(shell find $(SOURCE_DIR) -name "*Can*"),$(SOURCES))
endif
OBJECTS := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(OBJECT_DIR)/%.o)
DEPENDENCIES := $(SOURCES:$(SOURCE_DIR)/%.cpp=$(DEPENDENCY_DIR)/%.d)
CPPFLAGS += -g -Wall -Wextra -fdiagnostics-show-option -Wredundant-decls -Wshadow -Woverloaded-virtual -Iinclude
COLOR = [34m$(1)[0m

$(LIB): $(OBJECTS) | $(dir $(LIB))
	$(info $(call COLOR,Linking)    $@)
	@ar rsc $@ $?

clean:
	@rm -rf $(BUILD_DIR)

$(sort $(dir $(OBJECTS))) $(sort $(dir $(DEPENDENCIES))) $(dir $(LIB)):
	@mkdir -p $@

build/objects/idf/hidapi.o: CPPFLAGS += -Wno-sign-compare

.SECONDEXPANSION:

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPENDENCY_DIR)/%.d | $$(dir $$@)
	$(info $(call COLOR,Compiling)  $<)
	@$(CXX) -c -MMD -MP -MT $@ -MF $(DEPENDENCY_DIR)/$*.temp $(CPPFLAGS) -o $@ $<
	@mv $(DEPENDENCY_DIR)/$*.temp $(DEPENDENCY_DIR)/$*.d

$(DEPENDENCY_DIR)/%.d: | $$(dir $$@) ;

-include $(DEPENDENCIES)
