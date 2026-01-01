#ifndef GB_ERROR_H_
#define GB_ERROR_H_

#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

void gb_error(const char *fmt, ...);
#define gb_abort(fmt, ...) gb_error(fmt, ##__VA_ARGS__); abort();

void gb_info(const char *fmt, ...);

#endif // GB_ERROR_H_
