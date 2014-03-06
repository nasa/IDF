# Change these to fit your system
IDF_HOME = ${HOME}/idf
LIBUSB_HOME = /usr/include/libusb-1.0

# Don't change anything below this line
common = -I${IDF_HOME}/models -I${LIBUSB_HOME}

TRICK_CFLAGS += ${common}
TRICK_CXXFLAGS += ${common}

ifeq (${TRICK_HOST_TYPE},Linux)
TRICK_USER_LINK_LIBS += -lusb-1.0
endif
