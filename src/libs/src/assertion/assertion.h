#pragma once

#include <stdlib.h>
#include <assert.h>
#include <string>
#include "logging/logging.h"


logging::Log logger = logging::Log();


void __assert_func(const char *file,
                   int line,
                   const char *func,
                   const char *failedexpr) {
    snprintf(g_assert_info.msg, sizeof(g_assert_info.msg),
            "ASSERT: %s at %s\n", failedexpr, func);
    strncpy(g_assert_info.file, file, sizeof(g_assert_info.file));
    g_assert_info.line = line;

    __asm("bkpt 1");
}


void my_assert(const char *msg) {
  strncpy(g_assert_info.msg, msg, sizeof(g_assert_info.msg));
  __asm("bkpt 2");
}


#define MY_ASSERT(expr, msg) \
    do {                                        \
        if (!(expr)) {                          \
        PLOG_FATAL(msg);                        \
        my_assert(__FILENAME__, __LINE__);      \
        }                                       \
    } while (0)
