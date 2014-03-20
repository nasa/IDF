#ifdef __linux__
    #include "libusb/hid.c"
#else
    #include "mac/hid.c"
#endif
