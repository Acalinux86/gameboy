#include "./log.h"

void gb_error(const char *fmt, ...)
{
    fprintf(stderr, "\033[0;031mGB_ERROR: ");

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\033[0m\n");
}

void gb_info(const char *fmt, ...)
{
    fprintf(stdout, "\033[0;032mGB_INFO: ");

    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fprintf(stdout, "\033[0m\n");
}
