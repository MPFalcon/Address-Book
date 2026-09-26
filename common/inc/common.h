#ifndef COMMON_H
#    define COMMON_H
// NOLINTBEGIN(cert-*)
#    ifdef __STDC_LIB_EXT1__
#        define __STDC_WANT_LIB_EXT1__ 1
#    endif

#    include <errno.h>
#    include <inttypes.h>
#    include <stdarg.h>
#    include <stdio.h>
#    include <stdlib.h>
#    include <unistd.h>
#    include <string.h>
#    include <fcntl.h>

#    define STR(X) #X

#    ifndef NDEBUG

/**
 * @brief Print a formatted error message with source location.
 *
 * @param str The expression or function call that failed.
 */
#        ifdef __STDC_LIB_EXT1__
#            define ERRORPRINTF(str)                   \
                fprintf_s(stderr,                      \
                          "%s:%s:%d: Failed %s; %s\n", \
                          __FILE__,                    \
                          __func__,                    \
                          __LINE__,                    \
                          STR(str),                    \
                          strerror(errno))
#        else
// NOLINTBEGIN(clang-analyzer-security.insecureAPI.*)
#            define ERRORPRINTF(str)                 \
                fprintf(stderr,                      \
                        "%s:%s:%d: Failed %s; %s\n", \
                        __FILE__,                    \
                        __func__,                    \
                        __LINE__,                    \
                        STR(str),                    \
                        strerror(errno))
// NOLINTEND(clang-analyzer-security.insecureAPI.*)
#        endif

/**
 * @brief Print a formatted debug message with source location.
 *
 * @param format Format string for the debug output.
 * @param ... Format arguments.
 */
static inline void __attribute__((format(printf, 4, 5))) debug_printf(
    const char * file,
    const char * function,
    int          line,
    const char * format,
    ...)
{
    va_list arguments;

    printf("%s:%s:%d: ", file, function, line);
    va_start(arguments, format);
    vprintf(format, arguments);
    va_end(arguments);
    printf(" \n");
}

#        define DEBUGPRINTF(...) \
            debug_printf(__FILE__, __func__, __LINE__, __VA_ARGS__)
#    else
#        define ERRORPRINTF(fmt)
#        define DEBUGPRINTF(...) ((void)0)
#    endif
//  NOLINTEND(cert-*):

/**
 * @brief Enumerated type for status codes.
 */
enum status_codes
{
    ERROR = (-1),
    SUCCESS,
    FAILURE,
};

#endif /* COMMON_H */

// EOF
