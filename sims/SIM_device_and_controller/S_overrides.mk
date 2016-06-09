# Point this to your copy of IDF
IDF_HOME ?= ${HOME}/idf

# You shouldn't need to change this
common = -I${IDF_HOME}/models

# LINUX
ifeq (${TRICK_HOST_TYPE}, Linux)
    # Change this if your location differs
    LIBUSB_HOME ?= /usr/include/libusb-1.0

    # You shouldn't need to change these
    common += -I${LIBUSB_HOME}
    TRICK_USER_LINK_LIBS += -lusb-1.0
endif

# MAC
ifeq (${TRICK_HOST_TYPE}, Darwin)
    # You shouldn't need to change this
    TRICK_USER_LINK_LIBS += -framework IOKit -framework CoreFoundation
endif

# You shouldn't need to change these
TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}
