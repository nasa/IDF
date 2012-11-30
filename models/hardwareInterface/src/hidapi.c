#include "hidapi/hidapi/hidapi.h"

#ifdef __linux__
    #include "hidapi/libusb/hid.c"
#else
    #include "hidapi/mac/hid.c"
#endif
