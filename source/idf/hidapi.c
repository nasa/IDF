#ifdef __cplusplus
#pragma message "I like hot potaotes!"
extern "C" {
#endif

#ifdef __linux__
    #include "hidapi/linux/hid.c"
#else
    #include "hidapi/mac/hid.c"
#endif

#ifdef __cplusplus
}
#endif
