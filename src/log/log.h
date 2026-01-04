#ifndef GB_ERROR_H_
#define GB_ERROR_H_

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

typedef enum GbLogLevel {
    GB_LOG_DEBUG = 0,
    GB_LOG_INFO  = 1,
    GB_LOG_WARN  = 2,
    GB_LOG_ERROR = 3,
    GB_LOG_FATAL = 4,
    GB_LOG_ABORT = 5,
    GB_LOG_ASSERT = 6,
} GbLogLevel;

typedef struct GbCSourceFile {
    char **c_src_files;
    int count;
    int capacity;
} GbCSourceFile;

typedef struct GbLogger {
    const char *gb_dir;
    GbLogLevel min_level;
    FILE *log_file;
    size_t max_file_len;
    bool use_color;
    bool use_timestamp;
    bool log_to_file;
    bool log_to_console;
    GbCSourceFile *files;
} GbLogger;

// Extern The Global Logger
extern GbLogger Logger;

// ANSI color codes
#define GB_LOG_COLOR_RESET   "\033[0m"
#define GB_LOG_COLOR_DEBUG   "\033[36m"  // Cyan
#define GB_LOG_COLOR_INFO    "\033[32m"  // Green
#define GB_LOG_COLOR_WARN    "\033[33m"  // Yellow
#define GB_LOG_COLOR_ERROR   "\033[31m"  // Red
#define GB_LOG_COLOR_FATAL   "\033[35m"  // Magenta
#define GB_LOG_COLOR_TIME    "\033[90m"  // Dark gray

#define GB_LOG_COLOR_ABORT   "\033[37;41m"  // White Text, Red Background
#define GB_LOG_COLOR_ASSERT  "\033[37;41m"  // White Text, Red Background

const char* gb_log_level_string(GbLogLevel level);
const char* gb_log_level_color (GbLogLevel level);

void gb_log_init(const char *gb_dir, const char *filename, GbLogLevel min_level);
void gb_log_shutdown(void);
void gb_log(GbLogLevel level, const char *file, int line, const char *fmt, ...);
void gb_log_set_level(GbLogLevel level);
void gb_log_set_color(bool enable);
void gb_log_set_timestamp(bool enable);

#define GB_ERROR(...) do { gb_log(GB_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__); } while (0)
#define GB_WARN(...)  do { gb_log(GB_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__); } while (0)
#define GB_FATAL(...) do { gb_log(GB_LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__); } while (0)
#define GB_DEBUG(...) do { gb_log(GB_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__); } while (0)
#define GB_INFO(...)  do { gb_log(GB_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__); } while (0)

// Special Log Case: the Program Aborts
#define GB_ABORT(...) do { gb_log(GB_LOG_ABORT, __FILE__, __LINE__, __VA_ARGS__); abort(); } while (0)

// Special Log Case: Assertion Errors
#define GB_ASSERT(expr, ...) do { if (!(expr)) { gb_log(GB_LOG_ASSERT, __FILE__, __LINE__, "Assertion Error: "#expr, ##__VA_ARGS__); exit(EXIT_FAILURE); } } while (0)

#define GB_C_SRC_FILES_CAPACITY 5
#define GB_GROW_CAPACITY(capacity) capacity == 0 ? GB_C_SRC_FILES_CAPACITY : capacity * 2;
#define GB_GROW_FILES_ARRAY(old_ptr, new_ptr, new_cap) do { new_ptr = realloc((old_ptr), sizeof(*(old_ptr))*new_cap); GB_ASSERT(new_ptr); } while (0)

const char *gb__log_get_src_file(const GbCSourceFile *files, const int index);

#endif // GB_ERROR_H_
