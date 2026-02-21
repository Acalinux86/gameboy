#include "disasm.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void tmp_sprintf(char *buf, const char *fmt, ...)
{
    memset(buf, 0, MAX_TMP_BUF_SIZE);

    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
}

/* Caller Must Free the Returned String */
static inline char *__sm83_strdup(char *src)
{
    /* Calculate The Length of the String */
    size_t length = strlen(src);

    /*
      Malloc Size of Src string + 1 for null termination
     */
    char *dst = (char *)malloc(sizeof(*dst) * (length + 1));
    if (dst == NULL)
    {
        fprintf(stderr, "Failed to Allocate Memory For String Duplication: `%s`\n", src);
        return NULL;
    }

    /* Copy the Source String into Destination String */
    strcpy(dst, src);

    /* Null Terminate the String */
    dst[length] = '\0';

    /* Return Destination String */
    return dst;
}

/* Function that Appends a string to disassembly buffer */
int sm83_disasm_append(struct Disasm *disasm, char *buffer)
{
    if (disasm == NULL || buffer == NULL) return -1;

    if (disasm->disasm_size >= disasm->disasm_cap)
    {
        disasm->disasm_cap = disasm->disasm_cap == 0 ? DISASM_CAP : disasm->disasm_cap * 2 ;
        disasm->disasm_items = realloc(disasm->disasm_items, sizeof(*disasm->disasm_items) * disasm->disasm_cap);
        if (disasm->disasm_items == NULL)
        {
            fprintf(stderr, "ERROR: Memory Reallocation foe disasm->disasm_items failed\n");
            return -1;
        }
    }

    disasm->disasm_items[disasm->disasm_size++] = __sm83_strdup(buffer);
    return 0;
}

/* Dump the Disassembly Contents into a file */
void sm83_dump_disasm(const struct Disasm *disasm, FILE *fp)
{
    for (size_t i = 0; i < disasm->disasm_size; ++i)
    {
        fprintf(fp, "%s", disasm->disasm_items[i]);
    }
}
