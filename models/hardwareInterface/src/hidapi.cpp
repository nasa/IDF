#ifdef __linux__
    #include "hidapi/linux/hid.c"
#else
    #include "hidapi/mac/hid.c"
#endif
