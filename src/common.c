#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned char *read_file(const char *filepath, size_t *file_size)
{
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: Could not read `%s`: `%s`\n", filepath, strerror(errno));
        return NULL;
    }

    int ret = fseek(fp, 0, SEEK_END);
    if (ret < 0) {
        fprintf(stderr, "ERROR: Could not seek to end of `%s`: `%s`\n", filepath, strerror(errno));
        fclose(fp);
        return NULL;
    }

    size_t size = ftell(fp);
    if (size <= 0) {
        fprintf(stderr, "ERROR: File `%s` Empty\n", filepath);
        fclose(fp);
        return NULL;
    }

    rewind(fp); // Rewind the file pointer to the beginning

    unsigned char *buffer = (unsigned char *)malloc(size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR: Memory Allocation Failed\n");
        fclose(fp);
        return NULL;
    }

    size_t bytes = fread(buffer, sizeof(*buffer), size, fp);
    if (bytes != (size_t)size) {
        fprintf(stderr, "ERROR: fread() failed: Expected %ld bytes got %zu bytes\n", size, bytes);
        free(buffer);
        fclose(fp);
        return NULL;
    }
    buffer[bytes] = '\0'; // Null Terminate

    *file_size = size;
    fclose(fp); // close file pointer
    return buffer;
}
