#include "mmu.h"
#include "sm83_cpu.h"
#include "common.c"

#define INITIALIZE_PROGRAM_COUNTER 0x0000

/* Global Temporary Variable to append the disassembly String. */
char tmp_buf[MAX_TMP_BUF_SIZE];

int main(void)
{
    /* Open the Rom File into memory */
    const char *file_path = "data/roms/tetris.gb";

    FILE *gfp = fopen(file_path, "rb");
    if (gfp == NULL)
    {
        fprintf(stderr, "ERROR: Failed To Open file: `%s`\n", file_path);
        return -1;
    }

    /* Initialize the Cpu */
    struct SM83CPU cpu = {0};
    enum SM83Error ret = sm83_cpu_init(&cpu, gfp, INITIALIZE_PROGRAM_COUNTER);
    if (ret != SM83_OK)
    {
        fprintf(stderr, "ERROR: Failed to Initialize because of %s\n", sm83_error_string(ret));
        return 1;
    }

    /* Emit Disassembly */
    sm83_cpu_emit_disasm(&cpu, 1);

    /* Emit Disassembly */
    EMIT_DISASM(1, SM83_ERR_DISASM, &cpu.disasm, ";; Automatically Generated Disassembly File of %s\n", file_path);

    /* Fetch => Decode => Execute Loop Cycle */
    while (1)
    {
        enum SM83Error decode = sm83_decode(&cpu);
        if (decode != SM83_OK)
        {
            fprintf(stderr, "ERROR: Failed to Decode Opcodes because of %s\n", sm83_error_string(decode));
            break;
        }
    }

    /* File to Be Dump Rom Assembly*/
    const char *asm_file = "data/disasm/tetris.asm";

    /* Open File For writing */
    FILE *fp = fopen(asm_file, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR: Fail to Open File: %s\n", asm_file);
        return 1;
    }

    /* Dump the Disassembly */
    sm83_dump_disasm(&cpu.disasm, fp);

    /* Close Disassembly File Pointer */
    fclose(fp);

    /* Close Game File Pointer */
    fclose(gfp);

    /* Shutdown the CPU */
    enum SM83Error error = sm83_cpu_shutdown(&cpu);

    if (error != SM83_OK)
    {
        fprintf(stderr, "ERROR: Failed to Shutdown CPU because of %s\n", sm83_error_string(ret));
        return 1;
    }
    return 0;
}
