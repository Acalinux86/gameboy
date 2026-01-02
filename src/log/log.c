#include "./log.h"

#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

GbLogger Logger = {
    .gb_dir = NULL,
    .min_level = GB_LOG_INFO,
    .log_file = NULL,
    .use_color = true,
    .use_timestamp = true,
    .log_to_file = false,
    .log_to_console = true,
    .files = NULL,
};

const char* gb_log_level_string(const GbLogLevel level)
{
    switch (level) {
        case GB_LOG_DEBUG:  return "DEBUG ";
        case GB_LOG_INFO:   return "INFO  ";
        case GB_LOG_WARN:   return "WARN  ";
        case GB_LOG_ERROR:  return "ERROR ";
        case GB_LOG_FATAL:  return "FATAL ";
        case GB_LOG_ABORT:  return "ABORT ";
        case GB_LOG_ASSERT: return "ASSERT";
        default:            return "UNKNOWN";
    }
}

const char* gb_log_level_color(const GbLogLevel level)
{
    switch (level) {
        case GB_LOG_DEBUG: return GB_LOG_COLOR_DEBUG;
        case GB_LOG_INFO:  return GB_LOG_COLOR_INFO;
        case GB_LOG_WARN:  return GB_LOG_COLOR_WARN;
        case GB_LOG_ERROR: return GB_LOG_COLOR_ERROR;
        case GB_LOG_FATAL: return GB_LOG_COLOR_FATAL;
        case GB_LOG_ABORT: return GB_LOG_COLOR_ABORT;
        case GB_LOG_ASSERT: return GB_LOG_COLOR_ASSERT;
        default:           return GB_LOG_COLOR_RESET;
    }
}

// Custom string duplicate implementation
static inline char *gb__log_str_dup(const char *src)
{
    const size_t len = strlen(src);
    char *temp = (char *)malloc(len + 1);
    assert(temp != NULL && "source duplication Failed.");
    memcpy(temp, src,len + 1);
    return temp;
}

static GbCSourceFile *gb__log_alloc_files(void)
{
    GbCSourceFile *files = (GbCSourceFile*)malloc(sizeof(GbCSourceFile));
    assert(files != NULL);
    files->count = 0;
    files->capacity = GB_C_SRC_FILES_CAPACITY;

    files->c_src_files = malloc(sizeof(*files->c_src_files) * files->capacity);
    assert(files->c_src_files != NULL);
    return files;
}

static inline void gb__log_set_src_file(GbCSourceFile *files, char *c_src_file)
{
    if (files == NULL) return;

    if (files->count >= files->capacity) {
        const int new_cap = GB_GROW_CAPACITY(files->capacity);
        char **new_ptr = NULL;
        GB_GROW_FILES_ARRAY(files->c_src_files, new_ptr, new_cap);
        files->c_src_files = new_ptr;
    }
    files->c_src_files[files->count++] = c_src_file;
}

static inline const char *gb__log_get_src_file(const GbCSourceFile *files, const int index)
{
    GB_ASSERT(index < files->count && index > 0, "Index: %d Out of Bounds(0, %d)", index, files->count);
    const char *src_file = files->c_src_files[index];
    return src_file;
}

static inline size_t gb__determine_max_file_len(const GbCSourceFile *files)
{
    size_t max = 0;
    for (int i = 0; i < files->count; ++i) {
        const char *filename = files->c_src_files[i];
        const size_t file_len = strlen(filename);
        if (file_len > max) {
            max = file_len;
        }
    }
    return max;
}

// We are only Allowing C Source files to be logged
bool gb__log_validate_c_file(const char *filename)
{
    const size_t len = strlen(filename);
    return filename[len - 1] == 'c' && filename[len - 2] == '.';
}

#define GB_PATH_MAX 256
static void gb__log_extract_c_src_files(const char *path)
{
    DIR *dir;
    struct dirent *ent;
    char full_path[GB_PATH_MAX];
    struct stat statbuf;

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            // Skip . and ..
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            // Create full path
            snprintf(full_path, sizeof(full_path), "%s/%s", path, ent->d_name);

            // Check if we can stat the file
            if (stat(full_path, &statbuf) == -1) {
                perror("stat");
                continue;  // Skip if we can't stat
            }

            // Append the entry to the global Logger.files Array
            char *file = gb__log_str_dup(ent->d_name);
            assert(file != NULL);

            const bool valid_c_file = gb__log_validate_c_file(file);
            if (valid_c_file) {
                gb__log_set_src_file(Logger.files, file);
            } else {
                free(file);
            }

            // If it's a directory, recurse into it
            if (S_ISDIR(statbuf.st_mode)) {
                gb__log_extract_c_src_files(full_path);
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("opendir");
        exit(EXIT_FAILURE);
    }
}

static inline void gb__set_src_dir_name(const char *name)
{
    Logger.gb_dir = name;
}

void gb_log_init(const char *gb_dir, const char *filename, const GbLogLevel min_level)
{
    gb_log_set_level(min_level);
    gb__set_src_dir_name(gb_dir);
    Logger.files = gb__log_alloc_files();
    gb__log_extract_c_src_files(Logger.gb_dir);
    assert(Logger.files->count > 0);
    const size_t max_file_len = gb__determine_max_file_len(Logger.files);
    Logger.max_file_len = max_file_len;

    if (filename != NULL) {
        Logger.log_file = fopen(filename, "a");
        if (Logger.log_file != NULL) {
            Logger.log_to_file = true;
        } else {
            fprintf(stderr, "[LOGGER] Failed to open log file: %s\n", filename);
        }
    }
}

void gb_log_shutdown(void)
{
    if (Logger.log_file != NULL) {
        fclose(Logger.log_file);
        Logger.log_file = NULL;
        Logger.log_to_file = false;
    }

    // Free Allocated Memory
    for (int i = 0; i < Logger.files->count; ++i) {
        free(Logger.files->c_src_files[i]);
        Logger.files->c_src_files[i] = NULL;
    }
    free(Logger.files->c_src_files);
    Logger.files->c_src_files = NULL;
    Logger.files->capacity = 0;
    Logger.files->count = 0;
    free(Logger.files);
    Logger.files = NULL;
}

FILE * gb__log_match_level_to_stream(const GbLogLevel level)
{
    switch (level) {
    case GB_LOG_INFO:
    case GB_LOG_WARN:
    case GB_LOG_DEBUG:
        return stdout;

    case GB_LOG_ERROR:
    case GB_LOG_FATAL:
    case GB_LOG_ABORT:
    case GB_LOG_ASSERT:
        return stderr;
    default:
        return NULL;
    }
}

void gb_log(const GbLogLevel level, const char *file, const int line, const char *fmt, ...)
{
    if (level < Logger.min_level) {
        return;
    }

    char timestamp[64] = {0};
    if (Logger.use_timestamp) {
        const time_t now = time(NULL);
        const struct tm *tm_info = localtime(&now);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);
    }

    // Get just the filename without path
    const char *filename = strrchr(file, '/');
    filename = filename ? filename + 1 : file;

    // Determine the Max File Length for Aligning Logs
    const size_t max_file_len = Logger.max_file_len;
    va_list args;

    // Log to console
    if (Logger.log_to_console) {
        FILE *stream = gb__log_match_level_to_stream(level);
        assert(stream != NULL);
        if (Logger.use_color) {
            if (Logger.use_timestamp) {
                fprintf(stderr, "%s[%s]%s %s[%s]%s %*s:%04d: ",
                       GB_LOG_COLOR_TIME, timestamp, GB_LOG_COLOR_RESET,
                       gb_log_level_color(level), gb_log_level_string(level),
                        GB_LOG_COLOR_RESET, (int)max_file_len, filename, line);
            } else {
                fprintf(stream, "%s[%s]%s %s:%4d: ",
                gb_log_level_color(level), gb_log_level_string(level),
                GB_LOG_COLOR_RESET, filename, line);
            }
        } else {
            if (Logger.use_timestamp) {
                fprintf(stream, "[%s] [%s] %s:%d: ",
                       timestamp, gb_log_level_string(level), filename, line);
            } else {
                fprintf(stream, "[%s] %s:%d: ",
                       gb_log_level_string(level), filename, line);
            }
        }

        va_start(args, fmt);
        vfprintf(stream, fmt, args);
        va_end(args);
        fprintf(stream, "\n");
    }

    // Log to file
    if (Logger.log_to_file && Logger.log_file != NULL) {
        if (Logger.use_timestamp) {
            fprintf(Logger.log_file, "[%s] [%s] %s:%d: ",
                   timestamp, gb_log_level_string(level), filename, line);
        } else {
            fprintf(Logger.log_file, "[%s] %s:%d: ",
                   gb_log_level_string(level), filename, line);
        }

        va_start(args, fmt);
        vfprintf(Logger.log_file, fmt, args);
        va_end(args);
        fprintf(Logger.log_file, "\n");
        fflush(Logger.log_file);
    }
}

void gb_log_set_level(const GbLogLevel level)
{
    Logger.min_level = level;
}

void gb_log_set_color(bool enable)
{
    Logger.use_color = enable;
}

void gb_log_set_timestamp(bool enable)
{
    Logger.use_timestamp = enable;
}
