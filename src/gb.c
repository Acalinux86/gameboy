#include "mmu.h"
#include "sm83_cpu.h"
#include "common.c"

#define INITIALIZE_PROGRAM_COUNTER 0x0000

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
    int ret = sm83_cpu_init(&cpu, gfp, INITIALIZE_PROGRAM_COUNTER);
    if (ret != 0) return 1;

    /* Emit Disassembly */
    sm83_cpu_emit_disasm(&cpu, 1);

    /* Fetch => Decode => Execute Loop Cycle */
    while (1)
    {
        if (sm83_decode(&cpu) != 0)
        {
            fprintf(stderr, "ERROR: Decode ERROR\n");
            break;
        }
        // if (cpu.registers.pc >= INITIALIZE_PROGRAM_COUNTER + size) break;
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
    sm83_cpu_shutdown(&cpu);
    return 0;
}
