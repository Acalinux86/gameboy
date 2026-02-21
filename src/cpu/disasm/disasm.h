#ifndef DISASM_H_
#define DISASM_H_

#include <stdlib.h>
#include <stdio.h>

struct Disasm
{
    /*
     * char **disasm is a dynamic buffer of buffers,
     Contains the disassembly of the Rom.

     * Allocated when init sm83_cpu_init,
     Freed when sm83_cpu_shutdown is called,

      * size_t disasm_size is the size of the disasm.
      * size_t disasm_cap is the capacity of the disasm buffer.
      * disasm is dynamically reallocated if size reaches capacity,
      and capacity is increased.
    */
    char **disasm_items;
    size_t disasm_size;
    size_t disasm_cap;
};

void tmp_sprintf(char *buf, const char *fmt, ...);
int sm83_disasm_append(struct Disasm *disasm, char *buffer);
void sm83_dump_disasm(const struct Disasm *disasm, FILE *fp);

#define DISASM_CAP 128
#define MAX_TMP_BUF_SIZE 256
extern char tmp_buf[MAX_TMP_BUF_SIZE];

#define EMIT_DISASM(emit_status, err, disasm, ...)              \
    do {                                                        \
        if (emit_status) {                                      \
            tmp_sprintf(tmp_buf, __VA_ARGS__);                  \
            int __ret = sm83_disasm_append((disasm), tmp_buf);  \
            if (__ret != 0) return err;                         \
        }                                                       \
    } while (0)

#endif /* DISASM_H_*/
