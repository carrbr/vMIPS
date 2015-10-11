#include <stdarg.h>
#include <stdio.h>
#include "debug.h"

void debug_impl(char *format_str, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, format_str);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    printf("%s: ", __extension__ __FUNCTION__);
    vprintf(format_str, args);
#pragma GCC diagnostic pop
#endif
}

void debug2_impl(char *format_str, ...) {
#ifdef DEBUG2
    va_list args;
    va_start(args, format_str);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
    printf("%s: ", __extension__ __FUNCTION__);
    vprintf(format_str, args);
#pragma GCC diagnostic pop
#endif
}

